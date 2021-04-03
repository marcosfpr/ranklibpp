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

#include  "../../api/metric/MetricScorer.hpp"
#include  "../../api/learning/RankList.hpp"

#include <stdexcept>

using namespace ltr;

MetricScorer::MetricScorer(){this->depth=0;}

MetricScorer::~MetricScorer()= default;

MetricScorer::MetricScorer(const MetricScorer& ms){
    this->depth = ms.depth;
}

MetricScorer& MetricScorer::operator=(const MetricScorer& ms)= default;

void MetricScorer::setDepth(int d){
    this->depth = d;
}

int MetricScorer::getDepth() const{
    return this->depth;
}

double MetricScorer::score(DataSet& ds){
    double score = 0.0;
    for(auto& singleList : ds){
        score += this->score(singleList);
    }
    return score/ds.size(); // average score by rankLists
}

vector<int> MetricScorer::getRelevanceLabels(RankList& rl){
    vector<int> rel;
    rel.reserve(rl.size());
    for(int i = 0; i < rel.size(); i++){
        rel[i] = rl.get(i)->getLabel();
    }
    return rel;
}

double MetricScorer::score(RankList& rl){
    throw std::logic_error("No implementation of 'MetricScorer::score' provided");
}

unique_ptr<MetricScorer> MetricScorer::clone() const{
    throw std::logic_error("No implementation of 'MetricScorer::clone' provided");
}

string MetricScorer::toString(){
    throw std::logic_error("No implementation of 'MetricScorer::name' provided");

}