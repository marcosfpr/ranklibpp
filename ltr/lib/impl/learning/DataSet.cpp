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

#include "../../api/learning/DataPoint.hpp"
#include "../../api/learning/RankList.hpp"
#include "../../api/learning/DataSet.hpp"
#include "../../api/LtrError.hpp"

#include <filesystem> // filesystem
#include <fstream> // ifstream
#include <memory> // shared_ptr
#include <cstring> // strcmp

using std::shared_ptr;
using namespace ltr;

namespace fs = std::filesystem;

DataSet ltr::load_svmlight(const string& file)
{   
    DataSet data;

    fs::path path = fs::path(file.c_str());

    if (!fs::exists(path))
        throw LtrError("Error in DataSet::load_svmlight(): requesting unspecified file, file=" + file);

    std::ifstream input(file.c_str());

    string line;
    string actual_query_id;
    Sample actual_sample;

    while (std::getline(input, line))
    {
        shared_ptr<DataPoint> ptr = std::make_shared<DataPoint>(line);
        if (actual_query_id.empty() || std::strcmp(ptr->getID().c_str(), actual_query_id.c_str()) == 0) { // same qid
            actual_sample.push_back(ptr);
            actual_query_id = ptr->getID();
        }
        else {
            RankList rl(actual_sample);
            data.push_back(rl);
            actual_sample.clear();

            actual_sample.push_back(ptr);
            actual_query_id = ptr->getID();
        }
    }

    RankList rl(actual_sample);
    data.push_back(rl);

    return data;
}
