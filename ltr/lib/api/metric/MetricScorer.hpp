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


#ifndef METRIC_SCORER_HPP_
#define METRIC_SCORER_HPP_

#include <vector>
#include <memory>

#include "../learning/DataSet.hpp"

using std::vector;
using std::unique_ptr;

namespace ltr{
        
    class RankList;

    /**
     * @brief  A abstract retrieval measure computation interface. 
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
         * @param d depth
         */
        void setDepth(int d);

        /**
         * @brief Get the Depth value
         * 
         * @return int 
         */
        int getDepth() const;


        /**
         * @brief Return score for multiple RankLists
         * 
         * @param ds 
         * @return double 
         */
        virtual double score(DataSet& ds);

        /**
         * @brief Return score for a single RankList
         * 
         * @param rl
         * @return double 
         */
        virtual double score(RankList& rl); 

        /**
         * @brief Clone a MetricScorer pointer
         * 
         * @return std::unique_ptr<Material> 
         */
        virtual unique_ptr<MetricScorer> clone() const;

        /**
         * @brief Return string representation of model.
         * 
         * @return string 
         */
        virtual string toString();

    protected:

        /**
         * @brief Get the Relevance Labels of a RankList
         * 
         * @param rl 
         * @return vector<int> 
         */
        static vector<int> getRelevanceLabels(RankList& rl);
        
        int depth;
    };
};

#endif