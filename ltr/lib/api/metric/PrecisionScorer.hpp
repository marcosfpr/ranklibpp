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

#ifndef LTRPP_PRECISIONSCORER_HPP
#define LTRPP_PRECISIONSCORER_HPP

#include "MetricScorer.hpp"

namespace ltr{

    class RankList;
    /**
     * @brief This class computes MAP (Mean Average Precision) from the whole ranked list (like in RankLib).
     *
     */
    class PrecisionScorer : public MetricScorer{
    public:

        /**
         * @brief Construct a new PrecisionScorer object
         * @param k depth of precision analysis
         */
        explicit PrecisionScorer(int k=5);

        /**
         * @brief Construct a new PrecisionScorer object
         *
         * @param ms
         */
        PrecisionScorer(const PrecisionScorer& ms);


        /**
         * @brief Assignment operator for PrecisionScorer object
         *
         * @param ms
         * @return PrecisionScorer&
         */
        PrecisionScorer& operator=(const PrecisionScorer& ms);


        /**
         * @brief Compute MAP for a single RankList
         *
         * @param rl
         * @return double
         */
        double score(RankList& rl) override;

        /**
        * @brief Return score for multiple RankLists
        *
        * @param ds
        * @return double
        */
        double score(DataSet& ds) override;

        /**
         * @brief Clone MetricScorer object
         *
         * @return unique_ptr<MetricScorer>
         */
        unique_ptr<MetricScorer> clone() const override;

        /**
         * @brief Return string representation of model.
         *
         * @return string
         */
        string toString() override;
    };
};

#endif //LTRPP_PRECISIONSCORER_HPP
