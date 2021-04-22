// Copyright (c) 2021 LTR++ Project (Marcos Pontes)

//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:

//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.

//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#include "../../../api/learning/ensemble/AdaRank.hpp"
#include "../../../api/metric/MetricScorer.hpp"
#include "../../../api/LtrError.hpp"

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <cmath>

#include <boost/algorithm/string.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

using std::unique_ptr;
using std::vector;
using std::stringstream;
namespace pt = boost::property_tree;

using namespace ltr;

WeakRanker::WeakRanker(int featureID) : featureID(featureID) {}

WeakRanker::~WeakRanker() = default;

double WeakRanker::predict(ReadableDataPoint dp)
{
    return dp->getFeatureValue(featureID);
}

int WeakRanker::getFeature() const{
    return this->featureID;
}

AdaRank::AdaRank(DataSet dataset, unique_ptr<MetricScorer> scorer, vector<int> features, DataSet validationSet,
                 int iter, double tolerance, int maxConsecutive)

        : Ranker(move(dataset), move(scorer), move(features), move(validationSet))
{

    this->iter = iter;
    this->tolerance = tolerance;
    this->max_consecutive_selections = maxConsecutive;
    this->previous_training_score = 0.0;
    this->previous_validation_score = 0.0;

    this->consecutive_selections = 0;
    this->previous_feature = -1;

    this->sample_weights.resize(training_samples.size());
    double initial_weights = 1.0 / training_samples.size();
    std::fill(sample_weights.begin(), sample_weights.end(), initial_weights);
}

void AdaRank::setIter(int iter){
    this->iter = iter;
}

void AdaRank::setTolerance(double tolerance){
    this->tolerance = tolerance;
}

void AdaRank::setConsecutiveSelections(int consecutiveSelections){
    this->max_consecutive_selections = consecutiveSelections;
}

double AdaRank::evaluateWeakRanker(WeakRanker& wk){
    double score = 0.0;
    int i = 0;
    for(RankList& rl: training_samples) {
        wk.rank(rl);
        score += scorer->score(rl) * sample_weights[i++];
    }
    return score;
}

WeakRanker AdaRank::selectWeakRanker(){
    // o melhor ranker é aquele que ordena os documentos com base em uma única
    // característica de entrada.

    double best = -1.0;
    int best_feature = -1;

    for (int & feature : features) {
        if(used_features.find(feature) != used_features.end()) continue;

        WeakRanker wk_i(feature);

        double score_i = evaluateWeakRanker(wk_i);

        if (score_i > best){
            best = score_i;
            best_feature = feature;
        }
    }

    return WeakRanker(best_feature);
}

void AdaRank::learn(int start) {
    for(int it = start; it <= iter; it++) {

        // 1° fase: seleção de um classificador fraco.
        WeakRanker best_weak_ranker = selectWeakRanker();
        if (best_weak_ranker.getFeature() == -1) {
            log("Nenhuma feature encontrada!", warning);
            break;
        }

        // 2° fase: avaliação do classificador fraco (geração do "amount to say")
        auto weights_iterator = sample_weights.begin();
        double num = 0.0;
        double denom = 0.0;
        for (RankList& rl : training_samples){
            best_weak_ranker.rank(rl);
            double score = scorer->score(rl);
            num += (*weights_iterator) * (1.0 + score);
            denom += (*weights_iterator) * (1.0 - score);
            weights_iterator++;
        }

        double amount_to_say = 0.5 * std::log(num / denom);

        // 3° fase: atualizando o modelo

        rankers.push_back(best_weak_ranker);
        ranker_weights.push_back(amount_to_say);

        // 4° fase: avaliando o ensemble nos dados de treino e validação (geração do "amount to say")

        double train_score = 0.0;
        double total_score = 0.0;

        list<double> train_scores_list;

        for(RankList& rl: training_samples) {
            rank(rl);
            double score = scorer->score(rl);
            double exp_score = std::exp(-score);
            total_score += exp_score;
            train_score += score;

            train_scores_list.push_back(exp_score);
        }

        train_score /= training_samples.size();
        double delta = train_score + tolerance - previous_training_score;
        string status_train = (delta > 0) ? "OK" : "BAD";

        int selected_feature = best_weak_ranker.getFeature();

        if(previous_feature == selected_feature) {
            consecutive_selections++;
            if(consecutive_selections == max_consecutive_selections) {
                status_train = "SATURED";
                consecutive_selections = 0;
                used_features.insert(selected_feature);
            }
        }

        previous_feature = selected_feature;

        double val_score = 0.0;
        if((!validation_samples.empty()) && it % 1 == 0) {
           rank(validation_samples);
           val_score = scorer->score(validation_samples);
           if (val_score > score_validation) {
               score_validation = val_score;
               best_rankers = rankers;
               best_weights = ranker_weights;
           }
        }

        double train_improvement = train_score - previous_training_score;
        double val_improvement = val_score - previous_validation_score;

        printIter(it, selected_feature, train_score, train_improvement, val_score, val_improvement, status_train);

        if (delta <= 0) {
            rankers.pop_back();
            ranker_weights.pop_back();
            break;
        }

        previous_training_score = train_score;
        previous_validation_score = val_score;

        // 5° fase: atualizando a distribuição dos pesos dos exemplos
        auto scores_it = train_scores_list.begin();
        for (double& weight : sample_weights) {
            weight *= std::exp(-amount_to_say * (*scores_it++)) / total_score;
        }
    }
}

void AdaRank::fit(bool verbose){

    this->verbose = verbose;

    printHeader();

    learn(1);

    if ( (!validation_samples.empty()) && (!best_rankers.empty()) ){
        rankers = best_rankers;
        ranker_weights = best_weights;
    }

    if (rankers.empty())
        throw LtrError("Error in AdaRank::fit() : any weak ranker it's defined.");

    rank(training_samples);
    rank(validation_samples);

    score_training = scorer->score(training_samples);

    if (! validation_samples.empty())
        score_validation = scorer->score(validation_samples);

    printResults();
}

double AdaRank::predict(ReadableDataPoint dp){
    double score = 0.0;

    auto weights_iter = ranker_weights.begin();

    for (auto & ranker : rankers) {
        score += (*weights_iter) * (dp->getFeatureValue(ranker.getFeature()));
        weights_iter++;
    }

    return score;
}

void AdaRank::saveJSON(std::ofstream& file){
    pt::ptree root;

    root.put("model", "AdaRank");

    pt::ptree subtree;

    subtree.put("iter", iter);
    subtree.put("consecutiveSelections", max_consecutive_selections);
    subtree.put("tolerance", tolerance);

    if (!rankers.empty()) {
        pt::ptree subtree_weights;

        pt::ptree rankers_node;
        for(WeakRanker& wk : rankers) {
            pt::ptree child;
            child.put("", wk.getFeature());
            rankers_node.push_back(std::make_pair("", child));
        }
        subtree_weights.add_child("rankers", rankers_node);

        pt::ptree weights_node;
        for(double& w : ranker_weights) {
            pt::ptree child;
            child.put("", w);
            weights_node.push_back(std::make_pair("", child));
        }
        subtree_weights.add_child("amount_to_say", weights_node);

        subtree.add_child("weights", subtree_weights);
    }

    root.add_child("parameters", subtree);

    pt::write_json(file, root);
}

void AdaRank::loadJSON(std::ifstream& file){
    pt::ptree root;
    pt::read_json(file, root);

    if(std::strcmp(root.get<string>("model").c_str(), "AdaRank") != 0)
        throw LtrError("Error in AdaRank::loadJSON() : required model it's different of AdaRank.");

    pt::ptree params = root.get_child("parameters");

    iter = params.get<int>("iter");
    max_consecutive_selections = params.get<int>("consecutiveSelections");
    tolerance = params.get<double>("tolerance");

    if( params.count("weights") != 0 ) {
        pt::ptree weights = params.get_child("weights");

        rankers.clear();
        for (auto &kv : weights.get_child("rankers"))
            rankers.emplace_back(kv.second.get_value<int>());

        ranker_weights.clear();
        for (auto &kv : weights.get_child("amount_to_say"))
            rankers.emplace_back(kv.second.get_value<double>());
    }

}

int AdaRank::getIter() const {
    return iter;
}

int AdaRank::getConsecutiveSelections() const {
    return max_consecutive_selections;
}

double AdaRank::getTolerance() const {
    return tolerance;
}

void AdaRank::printHeader() {
    if (! verbose) return;
    ltr::log("AdaRank starts.", info, BOLDCYAN);
    ltr::log({"#Iter" , "Feature", this->scorer->toString() + "-T", "Improve-T", this->scorer->toString()+"-V", "Improve-V",
         "Status"}, true, "", {7, 8, 9, 9, 9, 9, 9});
}

void AdaRank::printIter(int it, int feature, double train_score, double train_improve, double val_score, double val_improve, string status){ // NOLINT(performance-unnecessary-value-param)
    if (! verbose) return;
    ltr::log({std::to_string(it), std::to_string(feature), std::to_string(train_score), std::to_string(train_improve),
         (val_score != 0.0) ? std::to_string(val_score) : "", (val_score != 0.0) ? std::to_string(val_improve) : "", status},
        false, {"", "", ltr::color_score(train_score), ltr::color_delta(train_improve),
                ltr::color_score(val_score), ltr::color_delta(val_improve), ltr::color_status(status)},{7, 8, 9, 9, 9, 9, 9});
}

void AdaRank::printResults() {

    log({7, 8, 9, 9, 9, 9, 9}); // finishing iter table

    log("AdaRank training finished.", info, CYAN);
    log({scorer->toString()+"-T", scorer->toString()+"-V"}, true, "", {9,9});
    log({std::to_string(score_training), (validation_samples.empty()) ? "" : std::to_string(score_validation)},
        false, {ltr::color_score(score_training), (validation_samples.empty()) ? "" : ltr::color_score(score_validation)},
        {9,9});

    log({9,9});
}
