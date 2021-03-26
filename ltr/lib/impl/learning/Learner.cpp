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

#include <algorithm>

#include "../../api/learning/Learner.hpp"
#include "../../api/LtrError.hpp"

using namespace ltr;

void Learner::rank(RankList& rl){
    vector<int> indexes(rl.size());
    vector<double> scores(rl.size());
    for(int i = 0; i < rl.size(); i++){
        indexes[i] = i;
        scores[i] = this->predict(rl.get(i));
    }
    std::sort(indexes.begin(), indexes.end(),
        [&](const int& a, const int& b) {
            return (scores[a] > scores[b]);
        }
    );

    rl.permute(indexes);
}

void Learner::rank(DataSet& ds){
    for(RankList& rl : ds)
        rank(rl);
}
