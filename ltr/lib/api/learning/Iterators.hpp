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


#ifndef ITERATORS_HPP_
#define ITERATORS_HPP_

#include <list>
#include <vector>

#include <memory>

using std::list;
using std::vector;

namespace ltr{
    class DataPoint;

    /**
     * @brief iterator of features datapoint
     * Values of each input feature of learner.
     */
    typedef vector<double> FeaturesContainer; 

    /**
     * @brief Define a readable datapoint
     * 
     */
    typedef std::shared_ptr<const DataPoint> ReadableDataPoint;

    /**
     * @brief A vector of readable datapoints is considered one sample
     *  for ltr algorithms.
     */
    typedef vector<ReadableDataPoint> Sample; 

};

#endif // ITERATORS_HPP_