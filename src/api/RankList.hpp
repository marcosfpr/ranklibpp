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
#include <memory>

using std::shared_ptr;
using std::vector;

class DataPoint;
class RankListImpl;

typedef vector<shared_ptr<DataPoint>> sample_t; 

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
    RankList(sample_t data_points);

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
    std::string toString();

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
    shared_ptr<DataPoint> get(int k) const;


    /**
     * @brief set a single datapoint
     * 
     * @param k 
     * @param dp 
     */
    void set(int k, shared_ptr<DataPoint> dp);

    /**
     * @brief Get the Ranking object
     * 
     * @param fid 
     * @return RankList*
     */
    RankList* getRanking(int fid);

    /**
     * @brief Get the Correct Ranking object
     * 
     * @return RankList*
     */
    RankList* getCorrectRanking();


private:

    RankListImpl* p_impl;

};

#endif
