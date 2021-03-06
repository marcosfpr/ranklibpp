/**
 * @file MetricScorer.cpp
 * @author Marcos Pontes
 * @brief 
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include  "../../api/metric/MetricScorer.hpp"
#include  "../../api/learning/RankList.hpp"
#include  "../../api/learning/DataPoint.hpp"
#include  "../../api/RankLibError.hpp"

using namespace ranklib;

MetricScorer::MetricScorer(){this->depth=0;}

MetricScorer::~MetricScorer(){}

MetricScorer::MetricScorer(const MetricScorer& ms){
    this->depth = ms.depth;
}


MetricScorer& MetricScorer::operator=(const MetricScorer& ms){
    this->depth = ms.depth;
    return *this;
}


void MetricScorer::setDepth(int depth){
    this->depth = depth;
}

int MetricScorer::getDepth(){
    return this->depth;
}

double MetricScorer::score(DataSet ds){
    double score = 0.0;
    for(DataSet::iterator it = ds.begin(); it != ds.end(); it++){
        RankList singlelist = *it;
        score += this->score(singlelist);
    }
    return score/ds.size(); // average score by ranklists
}

vector<int> MetricScorer::getRelevanceLabels(RankList& rl){
    vector<int> rel;
    rel.reserve(rl.size());
    for(int i = 0; i < rel.size(); i++){
        rel[i] = rl.get(i)->getLabel();
    }
    return rel;
}
