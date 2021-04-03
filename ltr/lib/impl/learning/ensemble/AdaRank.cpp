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

#include <boost/algorithm/string.hpp>
#include <boost/log/trivial.hpp>

#include <string>
#include <vector>
#include <memory>

using std::unique_ptr;
using std::vector;

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
    this->consecutiveSelections = maxConsecutive;

}

void AdaRank::setIter(int iter){
    this->iter = iter;
}

void AdaRank::setTolerance(double tolerance){
    this->tolerance = tolerance;
}

void AdaRank::setConsecutiveSelections(int consecutiveSelections){
    this->consecutiveSelections = consecutiveSelections;
}

double AdaRank::evaluateWeakRanker(unique_ptr<WeakRanker>& wk){
    double score = 0.0;
    int weight = 0;
    for(RankList rl: training_samples) {
        wk->rank(rl);
        score += scorer->score(rl) * sample_weights[weight++];
    }
    return score;
}

unique_ptr<WeakRanker> AdaRank::selectWeakRanker(){
    // o melhor ranker é aquele que ordena os documentos com base em uma única
    // característica de entrada.

    double best = -1.0;
    unique_ptr<WeakRanker> wk;

    for (int & feature : features) {
        if(used_features.find(feature) == used_features.end()) continue;

        unique_ptr<WeakRanker> wk_i = std::make_unique<WeakRanker>(feature);

        double score_i = evaluateWeakRanker(wk_i);

        if (score_i > best){
            best = score_i;
            wk = move(wk_i);
        }
    }

    return wk;
}

void AdaRank::initialize() {
    LOGGING(info) << "AdaRank starts.\n";
    LOGGING(info) << "********************************************************";
    this->log({"#Iter", "Feature", this->scorer->toString()+"-T", this->scorer->toString()+"-V", "Status"}, log_level::info);
}

void AdaRank::learn(int start) {

}

void AdaRank::fit(bool verbose){

}

double AdaRank::predict(ReadableDataPoint dp){
    return 0.0;
}

map<string, double> AdaRank::getParameters(){
    return  {{"iter", iter}, {"consecutiveSelections", consecutiveSelections}, {"tolerance", tolerance}};
}

void AdaRank::setParameters(map<string, double> parameters) {

    if (parameters.find( "iter" ) != parameters.end())
        this->iter = parameters["iter"];

    if (parameters.find( "consecutiveSelections" ) != parameters.end())
        this->consecutiveSelections = parameters["consecutiveSelections"];

    if (parameters.find( "tolerance" ) != parameters.end())
        this->tolerance = parameters["tolerance"];

    // TODO: intialize weights
}


string AdaRank::name() const {
    return "AdaRank";
}

int AdaRank::getIter() const {
    return iter;
}

int AdaRank::getConsecutiveSelections() const {
    return consecutiveSelections;
}

double AdaRank::getTolerance() const {
    return tolerance;
}

