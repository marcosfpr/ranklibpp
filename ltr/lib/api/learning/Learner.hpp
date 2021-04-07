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

#ifndef LEARNER_HPP_
#define LEARNER_HPP_

#include "RankList.hpp"
#include "DataSet.hpp"

namespace ltr {

    /**
     * @brief Base Learner Agent interface for LTR algorithms
     *  The capabilities of a LTR learner is to generate a score for a single DataPoint and to provide an entire rank for 
     *  a RankList or a DataSet.
     */
    class Learner {
    public:
        /**
         * @brief A Learner need to evaluate a single datapoint
         * 
         * @param dp 
         * @return double score prediction
         */
        virtual double predict(ReadableDataPoint dp) = 0;

        /**
         * @brief Perform ranking in samples
         * 
         * @param l 
         */
        void rank(DataSet& l);

        /**
         * @brief Perform ranking in one sample
         * 
         * @param rl 
         */
        void rank(RankList& rl);

    };

}
#endif