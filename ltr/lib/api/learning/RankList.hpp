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

#ifndef RANK_LIST_HPP_
#define RANK_LIST_HPP_

#include "DataPoint.hpp"

#include <string>
#include <vector>
#include <list>
#include <memory>

using std::shared_ptr;
using std::unique_ptr;
using std::vector;
using std::list;

namespace ltr{
    class RankListImpl;

    typedef vector<ReadableDataPoint> Sample; 

    /**
     * @brief A RankList is the object to be ranked by models.
     * @details A single RankList corresponds to one sample to train or predict.
     * 
     */
    class RankList {
    public:

        /**
         * @brief Construct a new RankList object
         * 
         * @param data_points Vector of datapoints corresponding to all datapoints for a single queryID.
         */
        RankList(Sample data_points);

        /**
         * @brief Construct a new RankList object
         * 
         * @param rl 
         * @param idx 
         * @param offset 
         */
        RankList(const RankList& rl, vector<int> idx, int offset=0);

        /**
         * @brief Construct a new RankList object
         * 
         * @param rl other ranklist
         */
        RankList(const RankList& rl);

        /**
         * @brief Construct a new RankList object
         * 
         * @param rl 
         */
        RankList(RankList&& rl);

            /**
         * @brief Assign operator for RankLists
         * 
         * @param dp other ranklist
         * @return RankList& 
         */
        RankList& operator=(const RankList& rl);

        /**
         * @brief Move operator for ranklists
         * 
         * @param rl 
         * @return RankList& 
         */
        RankList& operator=(RankList&& rl);

        /**
         * @brief Destroy the RankList object
         * 
         */
        ~RankList();

        /**
         * @brief Return string representation of a ranklist
         * 
         * @return std::string 
         */
        std::string toString() const;

        /**
         * @brief get size of ranklist
         * 
         * @return size_t 
         */
        size_t size();

        /**
         * @brief get a single datapoint
         * 
         * @param k 
         * @return DataPoint& 
         */
        ReadableDataPoint get(int k) const;

        /**
         * @brief get a referente to a single datapoint
         * 
         * @param i 
         * @return DataPoint& 
         */
        const DataPoint& operator[](size_t i);

        /**
         * @brief set a single datapoint
         * 
         * @param k 
         * @param dp 
         */
        void set(int k, ReadableDataPoint dp);


        /**
         * @brief Get the Ranking object
         * 
         * @param fid 
         * @return RankList
         */
        RankList getPartialRanking(int fid) const;

        /**
         * @brief Get the Correct Ranking object
         * 
         * @return RankList&&
         */
        RankList getRanking() const;

        /**
         * @brief Permute ranklist considering indexes
         * 
         * @param idx 
         */
        void permute(vector<int>& idx);

    private:

        RankListImpl* p_impl;

    };

};

#endif
