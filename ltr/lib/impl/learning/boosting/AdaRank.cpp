#include "../../../api/learning/boosting/AdaRank.hpp"

#include "../Ranker.cpp"

#include <list>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <iostream>               

#include "boost/filesystem.hpp"  

using std::move;
using std::string;
using std::vector;

using namespace ltr;


class ltr::AdaRankImpl : public ltr::RankerImpl {
public:

private:
    int nIteration, maxSelCount;
    bool enqueueTrain;
    double tolerance;

};



AdaRank::AdaRank(DataSet dataset, vector<int> features, unique_ptr<MetricScorer> scorer,
        int nIteration=30, double tolerance=0.002, bool enqueue=true, int maxSelCount=5){

        }


AdaRank::~AdaRank(){

}


AdaRank::AdaRank(const AdaRank& rk){

}


AdaRank& AdaRank::operator=(const AdaRank& rk){

}


void AdaRank::start(){

}


void AdaRank::learn(){

}


double AdaRank::eval(ReadableDataPoint dp){

}


string AdaRank::toString(){

}

string AdaRank::model(){

}

void AdaRank::loadString(string model){

}

string AdaRank::name(){

}

void AdaRank::print(){

}

void AdaRank::setIterations(int nIteration){

}


int AdaRank::getIterations(){

}

void AdaRank::setTolerance(double tolerance){

}

double AdaRank::getTolerance(){

}


void AdaRank::setEnqueue(bool enqueue){

}

bool AdaRank::getEnqueue(){ 

}

void AdaRank::setMaxSelCount(int maxSelCount){

}

int AdaRank::getMaxSelCount(){

}
