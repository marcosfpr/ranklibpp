/**
 * @file MAPScorer.hpp
 * @author Marcos Pontes
 * @brief Mean Average Precision scorer for RankLists
 * @version 0.1
 * @date 2021-02-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MAP_SCORER_HPP_
#define MAP_SCORER_HPP_

#include "MetricScorer.hpp"

namespace ranklib{

    class RankList;
    /**
     * @brief This class computes MAP (Mean Average Precision) from the whole ranked list (like in RankLib).
     * 
     */
    class MAPScorer : public MetricScorer{
    public:

        /**
         * @brief Construct a new MAPScorer object
         * 
         */
        MAPScorer();

        /**
         * @brief Construct a new MAPScorer object
         * 
         * @param ms 
         */
        MAPScorer(const MAPScorer& ms);


        /**
         * @brief Assignment operator for MAPScorer object
         * 
         * @param ms 
         * @return MAPScorer& 
         */
        MAPScorer& operator=(const MAPScorer& ms);


        /**
         * @brief Compute MAP for a single RankList
         * 
         * @param rl 
         * @return double 
         */
        double score(RankList rl);

        /**
         * @brief  Compute MAP for a list of RankLists
         * 
         * @param rls 
         * @return double 
         */
        double score(DataSet rls);

    };
};

#endif // MAP_SCORER_HPP_