/**
 * @file RankList.hpp
 * @author your name (you@domain.com)
 * @brief Definition of RankLists
 * @version 0.1
 * @date 2021-02-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef RANK_LIST_HPP_
#define RANK_LIST_HPP_

#include <string>
#include <vector>
#include <list>
#include <memory>

using std::shared_ptr;
using std::unique_ptr;
using std::vector;
using std::list;

namespace ltr{
    class DataPoint;
    class RankListImpl;

    typedef shared_ptr<const DataPoint> ReadableDataPoint;
    typedef vector<ReadableDataPoint> Sample; 

    /**
     * @brief This class implement the list of objects (each of which is a DataPoint) to be ranked. 
     * 
     */
    class RankList {
    public:

        /**
         * @brief Construct a new Rank List object
         * 
         * @param data_points 
         */
        RankList(Sample data_points);

        /**
         * @brief Construct a new Rank List object
         * 
         * @param rl 
         * @param idx 
         * @param offset 
         */
        RankList(const RankList& rl, vector<int> idx, int offset=0);

        /**
         * @brief Construct a new Rank List object
         * 
         * @param rl other ranklist
         */
        RankList(const RankList& rl);

        /**
         * @brief Construct a new Rank List object
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
