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


#include "../api/RankList.hpp"
#include "../api/RankLibError.hpp"
#include "../api/DataPoint.hpp"

using std::move;
using std::string;
using std::vector;
using std::shared_ptr;


class RankListImpl{
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

    void set(int k, shared_ptr<DataPoint> dp){
        if(k >= 0 && k < this->data_points.size()){
            this->data_points[k] = dp;
        }
        else
            throw RankLibError("Error in RankList::set with k="+k);
    }


    RankListImpl* getCorrectRanking(){
        vector<double> scores(this->data_points.size());
        for(int i=0; i < this->data_points.size(); i++){
            scores[i] = this->data_points[i]->getLabel();
        }
        vector<int> indexes(this->data_points.size());
        std::iota(indexes.begin(), indexes.end(), 0);
        std::stable_sort(indexes.begin(), indexes.end(),
                [scores](size_t t1, size_t t2){return scores[t1] > scores[t2];});
        
        return new RankListImpl(*this, move(indexes));
    }


    RankListImpl* getRanking(short fid){
        vector<float> scores(this->data_points.size());
        for(int i=0; i < this->data_points.size(); i++){
            scores[i] = this->data_points[i]->getFeatureValue(fid);
        }
        vector<int> indexes(this->data_points.size());
        std::iota(indexes.begin(), indexes.end(), 0);
        std::stable_sort(indexes.begin(), indexes.end(),
                [scores](size_t t1, size_t t2){return scores[t1] > scores[t2];});
        
        return new RankListImpl(*this, move(indexes));
    }

    void init(sample_t data_points) {
        this->data_points = data_points;
    }

    void initFrom(const RankListImpl& rl, std::vector<int> idx, int offset=0){
        this->data_points.resize(rl.data_points.size());
        for(size_t i = 0; i < idx.size(); i++) {
            this->data_points[i] = rl.get(idx[i]-offset);
        }
    }

    void initFrom(const RankListImpl& rl){
        this->data_points = rl.data_points;
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

void RankList::set(int k, shared_ptr<DataPoint> dp){
    p_impl->set(k, move(dp));
}

RankList* RankList::getRanking(int fid){
    RankListImpl* impl = p_impl->getRanking(fid);
    RankList* rl = this;
    rl->p_impl = impl;
    return rl;
}

RankList* RankList::getCorrectRanking(){
    RankListImpl* impl = p_impl->getCorrectRanking();
    RankList* rl = this;
    rl->p_impl = impl;
    return rl;
}
