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

#include "../../api/utils/KeyValue.hpp"
#include "boost/algorithm/string.hpp"

#include <vector>

using std::vector;
using ltr::KeyValue;


list<KeyValue> ltr::parseKeyValue(string raw, const string key_value_separator, const string pair_separator){
    vector<string> rawLines;
    boost::split(rawLines, raw, boost::is_any_of("\n"));

    list<KeyValue> result;

    for(string line : rawLines){
        boost::trim(line);

        vector<string> tokens;
        boost::split(tokens, line, boost::is_any_of(pair_separator));

        for(string token : tokens){
            vector<string> pair;

            boost::split(pair, token, boost::is_any_of(key_value_separator));
            
            KeyValue kv;
            kv.key = pair[0];
            kv.value = pair[1];

            result.push_back(kv);
        }
    }

    return result;
}
