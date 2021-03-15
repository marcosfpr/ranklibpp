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

#include "../../api/learning/Ranker.hpp"
#include "../../api/learning/RankList.hpp"
#include "../../api/learning/DataPoint.hpp"
#include "../../api/learning/DataSet.hpp"

#include "../../api/metric/MetricScorer.hpp"
#include "../../api/LtrError.hpp"

#include <list>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <iostream>    
#include <fstream>    
#include <stdexcept>           
#include <experimental/filesystem>

using std::move;
using std::unique_ptr;
using std::shared_ptr;
using std::string;
using std::list;
using std::vector;
namespace fs = std::experimental::filesystem;

using namespace ltr;

class ltr::RankerImpl {
public:

        RankerImpl(DataSet dataset, unique_ptr<MetricScorer> scorer, vector<int> features){
            init(move(dataset), move(features), move(scorer));
        }

        ~RankerImpl(){
            freePointers();
        }


        RankerImpl(const RankerImpl& rk){
            initFrom(rk);
        }

        void setTrainingSet(DataSet ds){
            this->training_samples = move(ds);
        }

        void setFeatures(vector<int> features){
            this->features = move(features);
        }

        void setValidationSet(DataSet ds){
            this->validation_samples = move(ds);
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

        double predict(ReadableDataPoint dp){
            return 0.0;
        }

        string model(){ 
            return "Generic Ranker Model";
        }

        void save(string fileToSave){
            fs::path path = fs::path(fileToSave.c_str());

            fs::path dir = path.parent_path();

            if(! fs::exists(dir))
                fs::create_directory(dir);
            
            std::ofstream file(fileToSave.c_str());
            file << model();
            file.close();
            
        }

        void rank(RankList& rl){
            vector<int> indexes(rl.size());
            vector<double> scores(rl.size());
            for(int i = 0; i < rl.size(); i++){
                indexes[i] = i;
                scores[i] = this->predict(rl.get(i));
            }
            std::sort(indexes.begin(), indexes.end(),
                [&](const int& a, const int& b) {
                    return (scores[a] > scores[b]);
                }
            );

            rl.permute(indexes);
        }

        void rank(DataSet& ds){
            for(RankList& rl : ds)
                rank(rl);
        }

        void init(DataSet dataset, vector<int> features, unique_ptr<MetricScorer> scorer){
            this->training_samples = move(dataset);
            this->features = move(features);
            this->scorer = move(scorer);
            this->score_training = 0.0;
            this->score_validation = 0.0;
        }

        void initFrom(const RankerImpl& rk){
            this->features = rk.features;
            this->scorer = rk.scorer->clone();
            this->training_samples.clear();
            for(RankList rl : rk.training_samples) {
                this->training_samples.push_back(RankList(rl));
            }
            this->validation_samples.clear();
            for(RankList rl : rk.validation_samples) {
                this->validation_samples.push_back(RankList(rl));
            }
        }

        void freePointers() {
            this->training_samples.clear();
            this->validation_samples.clear();
            this->features.clear();
        }

protected:
    DataSet training_samples, validation_samples;
    vector<int> features;
    unique_ptr<MetricScorer> scorer;
    double score_training, score_validation;

};


void Ranker::fit(){
   	throw std::logic_error("No implementation of 'Ranker::fit' provided");
}

double Ranker::predict(ReadableDataPoint dp){
    throw std::logic_error("No implementation of 'Ranker::predict' provided");
}


string Ranker::toString(){
    throw std::logic_error("No implementation of 'Ranker::toString' provided");
}


string Ranker::model(){
    throw std::logic_error("No implementation of 'Ranker::model' provided");
}


void Ranker::loadString(string model){
    throw std::logic_error("No implementation of 'Ranker::loadString' provided");
}


Ranker::Ranker(DataSet dataset, unique_ptr<MetricScorer> scorer, vector<int> features){
    this->p_impl = new RankerImpl(move(dataset), move(scorer), move(features));
}

Ranker::Ranker(const Ranker& rk){
    this->p_impl = new RankerImpl(*rk.p_impl);
}

Ranker& Ranker::operator=(const Ranker& rk){
    p_impl->initFrom(*rk.p_impl);
    return *this;
}

Ranker::~Ranker(){
    delete p_impl;
}

void Ranker::setTrainingSet(DataSet dataset){
    this->p_impl->setTrainingSet(move(dataset));
}

void Ranker::setFeatures(vector<int> features){
    this->p_impl->setFeatures(move(features));
}

void Ranker::setValidationSet(DataSet dataset){
    this->p_impl->setValidationSet(move(dataset));
}

void Ranker::setScorer(unique_ptr<MetricScorer> scorer){
    this->p_impl->setScorer(move(scorer));
}

double Ranker::getTrainingScore(){
    return this->p_impl->getTrainingScore();
}

double Ranker::getValidationScore(){
    return this->p_impl->getValidationScore();
}

vector<int> Ranker::getFeatures(){
    return this->p_impl->getFeatures();
}

void Ranker::rank(DataSet& l){
    this->p_impl->rank(l);
}

void Ranker::rank(RankList& rl){
    this->p_impl->rank(rl);
}

void Ranker::save(string fileToSave){
    this->p_impl->save(fileToSave);
}