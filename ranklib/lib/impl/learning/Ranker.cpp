/**
 * @file Ranker.cpp
 * @author Marcos Pontes
 * @brief Ranker class implementation.
 * @version 0.1
 * @date 2021-03-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "../../api/learning/Ranker.hpp"
#include "../../api/learning/RankList.hpp"
#include "../../api/learning/DataPoint.hpp"
#include "../../api/metric/MetricScorer.hpp"
#include "../../api/RankLibError.hpp"

#include <list>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>


using std::move;
using std::unique_ptr;
using std::shared_ptr;
using std::string;
using std::list;
using std::vector;

using namespace ranklib;

class RankerImpl {
public:

        virtual void init() = 0;

        virtual void learn() = 0;

        virtual double eval(ReadableDataPoint dp) = 0;

        virtual string toString() = 0;

        virtual string model() = 0;

        virtual void loadString(string model) = 0;

        virtual string name() = 0;

        virtual void print() = 0;


        RankerImpl(list<RankList> samples, vector<int> features, unique_ptr<MetricScorer> scorer){
            this->training_samples = move(samples);
            this->features = move(features);
            this->scorer = move(scorer);
            this->score_training = 0.0;
            this->score_validation = 0.0;
        }

        ~RankerImpl(){
            this->training_samples.clear();
            this->validation_samples.clear();
            this->features.clear();
        }


        RankerImpl(const RankerImpl& rk){
            this->features = rk.features;
            this->scorer = std::make_unique<MetricScorer>(rk.scorer);
            this->training_samples.clear();
            for(RankList rl : rk.training_samples) {
                this->training_samples.push_back(RankList(rl));
            }
            this->validation_samples.clear();
            for(RankList rl : rk.validation_samples) {
                this->validation_samples.push_back(RankList(rl));
            }
        }

        void setTrainingSet(list<RankList> samples){
            this->training_samples = move(samples);
        }

        void setFeatures(vector<int> features){
            this->features = move(features);
        }

        void setValidationSet(list<RankList> samples){
            this->validation_samples = move(samples);
        }


        void setScorer(unique_ptr<MetricScorer> scorer){
            this->scorer = move(scorer);
        }

        double getTrainingScore(){
            return this->score_training;
        }


        double getValidationScore(){
            return this->score_validation;
        }

        vector<int> getFeatures(){
            return this->features;
        }

        void rank(RankList& rl){
            vector<int> indexes(rl.size());
            vector<double> scores(rl.size());
            for(int i = 0; i < rl.size(); i++){
                indexes[i] = i;
                scores[i] = this->eval(rl.get(i));
            }
            std::sort(indexes.begin(), indexes.end(),
                [&](const int& a, const int& b) {
                    return (scores[a] > scores[b]);
                }
            );

            // todo: craete permutation method on RankList to reranking elements
        }

        void rank(list<RankList>* l){

        }

        void save(string fileToSave);

protected:
    list<RankList> training_samples, validation_samples;
    vector<int> features;
    unique_ptr<MetricScorer> scorer;
    double score_training, score_validation;

};


