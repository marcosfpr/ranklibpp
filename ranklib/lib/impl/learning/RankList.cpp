/**
 * @file RankList.cpp
 * @author Marcos Pontes
 * @brief RankList impl
 * @version 0.1
 * @date 2021-02-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <numeric>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <utility>


#include "../../api/learning/RankList.hpp"
#include "../../api/RankLibError.hpp"
#include "../../api/learning/DataPoint.hpp"

using std::move;
using std::string;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;

using namespace ranklib;

class ranklib::RankListImpl{
public:

    RankListImpl(sample_t data_points) {
        init(move(data_points));
    }


    RankListImpl(const RankListImpl& rl, std::vector<int> idx, int offset=0){
        initFrom(rl, move(idx), offset);
    }


    RankListImpl(const RankListImpl& rl){
        initFrom(rl);
    }


    ~RankListImpl(){
        freePointers();
    }


    std::string toString(){
        return "<RankList object with " + std::to_string(this->data_points.size()) + " samples>";
    }

    size_t size(){
        return this->data_points.size();
    }

    shared_ptr<DataPoint> get(int k) const{
        if(k >= 0 && k < this->data_points.size()){
            return this->data_points[k];
        }
        throw RankLibError("Error in RankList::get with k="+k);
    }

    DataPoint& operator[](size_t i){
        return *this->data_points[i];
    }

    void set(int k, shared_ptr<DataPoint> dp){
        if(k >= 0 && k < this->data_points.size()){
            this->data_points[k] = dp;
            return;
        }
        throw RankLibError("Error in RankList::set with k="+k);
    }


    void ranking(){
        std::stable_sort(data_points.begin(), data_points.end(),
                [](shared_ptr<DataPoint> dp1, shared_ptr<DataPoint> dp2)
                {
                    return dp1->getLabel() > dp2->getLabel();
                }
        );
    }


    void partialRanking(short fid){
        std::stable_sort(data_points.begin(), data_points.end(),
                [fid](shared_ptr<DataPoint> dp1, shared_ptr<DataPoint> dp2)
                {
                    return dp1->getFeatureValue(fid) > dp2->getFeatureValue(fid);
                }
        );
    }

    void init(sample_t data_points) {
        this->data_points = data_points;
    }

    void initFrom(const RankListImpl& rl, std::vector<int> idx, int offset=0){
        this->data_points.resize(rl.data_points.size());
        for(size_t i = 0; i < idx.size(); i++) {
            shared_ptr<DataPoint> ref = rl.get(idx[i]-offset);
            this->data_points[i] = std::make_shared<DataPoint>(DataPoint(*ref));
        }
    }

    void initFrom(const RankListImpl& rl){
        this->data_points.resize(rl.data_points.size());
        for(size_t i = 0; i < rl.data_points.size(); i++) {
            shared_ptr<DataPoint> ref = rl.get(i);
            this->data_points[i] = std::make_shared<DataPoint>(DataPoint(*ref));
        }
    }

    void freePointers(){
       data_points.clear();
    }

private:
    sample_t data_points;
};



RankList::RankList(sample_t data_points){
    this->p_impl = new RankListImpl(move(data_points));
}

RankList::RankList(const RankList& rl, vector<int> idx, int offset){
    this->p_impl = new RankListImpl(*rl.p_impl, move(idx), offset);
}

RankList::RankList(const RankList& rl){
    this->p_impl = new RankListImpl(*rl.p_impl);
}

RankList::RankList(RankList&& rl){
    this->p_impl = rl.p_impl;
    rl.p_impl = nullptr;
}

RankList& RankList::operator=(const RankList& rl){
    p_impl->initFrom(*rl.p_impl);
    return *this;
}

RankList& RankList::operator=(RankList&& rl){
    if(this != &rl)
    {
        delete p_impl;
        p_impl = rl.p_impl;
        rl.p_impl = nullptr;
    }
    return *this;
}

RankList::~RankList(){
    delete p_impl;
}

std::string RankList::toString(){
    return p_impl->toString();
}

size_t RankList::size(){
    return p_impl->size();
}

shared_ptr<DataPoint> RankList::get(int k) const{
    return p_impl->get(k);
}

DataPoint& RankList::operator[](size_t i){
    return (*p_impl)[i];
}

void RankList::set(int k, shared_ptr<DataPoint> dp){
    p_impl->set(k, move(dp));
}

RankList RankList::getPartialRanking(int fid){
    RankList rl(RankList(*this));
    rl.p_impl->partialRanking(fid);
    return rl;
}

RankList RankList::getRanking(){
    RankList rl(RankList(*this));
    rl.p_impl->ranking();
    return rl;
}
