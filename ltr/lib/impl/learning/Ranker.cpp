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

#include "../../api/LtrError.hpp"
#include "../../api/learning/Ranker.hpp"
#include "../../api/metric/MetricScorer.hpp"

#include <numeric> // iota
#include <vector> // vector
#include <memory> // shared_ptr, unique_ptr
#include <stdexcept>  // runtime error 
#include <experimental/filesystem> // filesystem
#include <fstream> // ifstream, ofstream

using std::map;
using std::move;
using std::unique_ptr;
using std::string;
using std::vector;
using std::stringstream;
namespace fs = std::experimental::filesystem;

using namespace ltr;

Ranker::Ranker(DataSet dataset, unique_ptr<MetricScorer> scorer, vector<int> features, DataSet validationSet){
    this->training_samples = move(dataset);
    this->features = move(features);
    this->scorer = move(scorer);
    this->score_training = 0.0;
    this->score_validation = 0.0;
    this->validation_samples = move(validationSet);
    this->verbose = false;

    if(this->features.empty()) {
        this->extractFeatures();
    }

    ltr::init_logging();
}

Ranker::~Ranker(){
    this->training_samples.clear();
    this->validation_samples.clear();
    this->features.clear();
}

void Ranker::setTrainingSet(DataSet ds){
    this->training_samples = move(ds);
}

void Ranker::setFeatures(vector<int> ft){
    this->features = move(ft);
}

void Ranker::setValidationSet(DataSet ds){
    this->validation_samples = move(ds);
}


void Ranker::setScorer(unique_ptr<MetricScorer> scr){
    this->scorer = move(scr);
}

double Ranker::getTrainingScore() const{
    return this->score_training;
}


double Ranker::getValidationScore() const{
    return this->score_validation;
}

vector<int> Ranker::getFeatures(){
    return this->features;
}


void Ranker::save(const string& fileToSave){
    fs::path path = fs::path(fileToSave.c_str());

    fs::path dir = path.parent_path();

    if(! fs::exists(dir))
        fs::create_directory(dir);

    std::ofstream file(fileToSave.c_str());

    try {
        this->saveJSON(file);
        file.close();
    }
    catch (std::logic_error& e) {
        file.close();
        fs::remove(path);
        throw e;
    }
}

void Ranker::load(const string& fileToLoad) {
    fs::path path = fs::path(fileToLoad.c_str());

    if(! fs::exists(path))
        throw LtrError("Error in Ranker::load with path="+ fileToLoad);

    std::ifstream file(fileToLoad.c_str());

    this->loadJSON(file);

    file.close();
}

void Ranker::fit(){
   	throw std::logic_error("No implementation of 'Ranker::fit' provided");
}

double Ranker::predict(ReadableDataPoint dp){
    throw std::logic_error("No implementation of 'Ranker::predict' provided");
}

void Ranker::loadJSON(std::ifstream& file){
    throw std::logic_error("No implementation of 'Ranker::loadJSON' provided");
}

void Ranker::saveJSON(std::ofstream& file) {
    throw std::logic_error("No implementation of 'Ranker::saveJSON' provided");
}

void Ranker::extractFeatures(){
    // basic impl. extract the first seen datapoint and use its
    // featuresCount value to create the feature vector representation
    if(!training_samples.empty()) {
        auto first = this->training_samples.begin();
        int maxFeature = first->get(0)->getFeatureCount();
        this->features.resize(maxFeature);
        std::iota(this->features.begin(), this->features.end(), 1);
    }
}
