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

namespace ltr{

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
        double score(RankList& rl) override;

        /**
         * @brief  Compute MAP for a list of RankLists
         * 
         * @param rls 
         * @return double 
         */
        double score(DataSet& rls);

        /**
         * @brief Clone MetricScorer object
         * 
         * @return unique_ptr<MetricScorer> 
         */
        unique_ptr<MetricScorer> clone() const override;

    };
};

#endif // MAP_SCORER_HPP_