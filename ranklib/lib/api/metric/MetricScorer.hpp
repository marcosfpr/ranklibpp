/**
 * @file MetricScorer.hpp
 * @author Marcos Pontes
 * @brief Generic retrieval measure computation interface (like Ranklib)
 * @version 0.1
 * @date 2021-02-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef METRIC_SCORER_HPP_
#define METRIC_SCORER_HPP_

#include <vector>
#include <memory>

#include "../learning/DataSet.hpp"

using std::vector;
using std::unique_ptr;

namespace ranklib{
        
    class RankList;

    /**
     * @author Marcos Pontes and vdang
     * @brief  A generic retrieval measure computation interface. 
     */
    class MetricScorer {
        
    public:
        /**
         * @brief Construct a new Metric Scorer object
         * 
         */
        MetricScorer();

        /**
         * @brief Destroy the Metric Scorer object
         * 
         */
        ~MetricScorer();
        
        /**
         * @brief Construct a new MetricScorert object
         * 
         * @param rl other MetricScorer
         */
        MetricScorer(const MetricScorer& ms);

        /**
         * @brief Assign operator for MetricScorer
         * 
         * @param dp other MetricScorer
         * @return MetricScorer& 
         */
        MetricScorer& operator=(const MetricScorer& ms);

        /**
         * @brief Set the Depth value
         * 
         * @param depth 
         */
        void setDepth(int depth);

        /**
         * @brief Get the Depth value
         * 
         * @return int 
         */
        int getDepth();


        /**
         * @brief Return score for multiple RankLists
         * 
         * @param ds 
         * @return double 
         */
        double score(DataSet& ds);

        /**
         * @brief Return score for a single RankList
         * 
         * @param rl
         * @return double 
         */
        virtual double score(RankList& rl) = 0;

        /**
         * @brief Clone a MetricScorer pointer
         * 
         * @return std::unique_ptr<Material> 
         */
        virtual unique_ptr<MetricScorer> clone() const = 0;

    protected:

        /**
         * @brief Get the Relevance Labels of a RankList
         * 
         * @param rl 
         * @return vector<int> 
         */
        vector<int> getRelevanceLabels(RankList& rl);
        
        int depth;
    };
};

#endif