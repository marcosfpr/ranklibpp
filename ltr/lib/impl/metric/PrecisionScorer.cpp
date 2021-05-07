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


#include "../../api/metric/PrecisionScorer.hpp"
#include "../../api/learning/RankList.hpp"

using namespace ltr;

PrecisionScorer::PrecisionScorer(int k):MetricScorer(){
    this->depth = k;
}

PrecisionScorer::PrecisionScorer(const PrecisionScorer& ms) = default;

PrecisionScorer& PrecisionScorer::operator=(const PrecisionScorer& ms)= default;


double PrecisionScorer::score(RankList& rl){
    double precision = 0.0;
    for (int i = 0; i < depth; i++) {
        if (rl.get(i)->getLabel() > 0) precision += 1;
    }
    return precision / depth;
}

unique_ptr<MetricScorer> PrecisionScorer::clone() const{
    return std::make_unique<PrecisionScorer>( *this );
}

double PrecisionScorer::score(DataSet &ds) {
    return MetricScorer::score(ds);
}

string PrecisionScorer::toString() {
    return "P@"+std::to_string(this->depth);
}
