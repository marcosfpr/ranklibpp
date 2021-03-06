/**
 * @file MAPScorer.cpp
 * @author Marcos Pontes
 * @brief Implementation of MAPScorer
 * @version 0.1
 * @date 2021-02-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../api/metric/MAPScorer.hpp"
#include "../../api/learning/RankList.hpp"
#include "../../api/learning/DataPoint.hpp"

using namespace ranklib;

MAPScorer::MAPScorer():MetricScorer(){}

MAPScorer::MAPScorer(const MAPScorer& ms):MetricScorer(ms){}

MAPScorer& MAPScorer::operator=(const MAPScorer& ms){
    MetricScorer::operator=(ms);
    return *this;
}

double MAPScorer::score(RankList rl){
    double averagePrecision = 0.0;
    int count = 0.0;
    for(int i=0; i < rl.size(); i++) {
        if(rl.get(i)->getLabel() > 0.0) {
            count++;
            averagePrecision += ((double)count/(i+1));
        }
    }
    return count > 0.0 ? averagePrecision / count : 0.0;
}

double MAPScorer::score(DataSet ds){
    return MetricScorer::score(std::move(ds));
}
