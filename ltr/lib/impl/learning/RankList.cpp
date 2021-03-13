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

#include <numeric>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <utility>


#include "../../api/learning/RankList.hpp"
#include "../../api/LtrError.hpp"
#include "../../api/learning/DataPoint.hpp"

using std::move;
using std::string;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;

using namespace ltr;

class ltr::RankListImpl{
public:

    RankListImpl(Sample data_points) {
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

    ReadableDataPoint get(int k) const{
        if(k >= 0 && k < this->data_points.size()){
            return this->data_points[k];
        }
        throw LtrError("Error in RankList::get with k="+k);
    }

    const DataPoint& operator[](size_t i){
        return *this->data_points[i];
    }

    void set(int k, ReadableDataPoint dp){
        if(k >= 0 && k < this->data_points.size()){
            this->data_points[k] = dp;
            return;
        }
        throw LtrError("Error in RankList::set with k="+k);
    }


    void ranking(){
        std::stable_sort(data_points.begin(), data_points.end(),
                [](ReadableDataPoint dp1, ReadableDataPoint dp2)
                {
                    return dp1->getLabel() > dp2->getLabel();
                }
        );
    }


    void partialRanking(short fid){
        std::stable_sort(data_points.begin(), data_points.end(),
                [fid](ReadableDataPoint dp1, ReadableDataPoint dp2)
                {
                    return dp1->getFeatureValue(fid) > dp2->getFeatureValue(fid);
                }
        );
    }

    void permute(vector<int>& idx) {
        Sample new_datapoints(this->data_points.size());
        for(int i=0; i < idx.size(); i++){
            new_datapoints[i] = this->data_points[idx[i]];
        }
        this->data_points = move(new_datapoints);
    }

    void init(Sample data_points) {
        this->data_points = data_points;
    }

    void initFrom(const RankListImpl& rl, std::vector<int> idx, int offset=0){
        this->data_points.resize(rl.data_points.size());
        for(size_t i = 0; i < idx.size(); i++) {
            ReadableDataPoint ref = rl.get(idx[i]-offset);
            this->data_points[i] = std::make_shared<DataPoint>(DataPoint(*ref));
        }
    }

    void initFrom(const RankListImpl& rl){
        this->data_points.resize(rl.data_points.size());
        for(size_t i = 0; i < rl.data_points.size(); i++) {
            ReadableDataPoint ref = rl.get(i);
            this->data_points[i] = std::make_shared<DataPoint>(DataPoint(*ref));
        }
    }

    void freePointers(){
       data_points.clear();
    }

private:
    Sample data_points;
};



RankList::RankList(Sample data_points){
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

std::string RankList::toString() const{
    return p_impl->toString();
}

size_t RankList::size(){
    return p_impl->size();
}

ReadableDataPoint RankList::get(int k) const{
    return p_impl->get(k);
}

const DataPoint& RankList::operator[](size_t i){
    return (*p_impl)[i];
}

void RankList::set(int k, ReadableDataPoint dp){
    p_impl->set(k, move(dp));
}

RankList RankList::getPartialRanking(int fid) const{
    RankList rl(RankList(*this));
    rl.p_impl->partialRanking(fid);
    return rl;
}

RankList RankList::getRanking() const{
    RankList rl(RankList(*this));
    rl.p_impl->ranking();
    return rl;
}

void RankList::permute(vector<int>& idx) {
    this->p_impl->permute(idx);
}
