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

#include "../../api/utils/Logging.hpp"
#include "../../api/LtrError.hpp"

#include <iomanip>
#include <sstream>
#include <utility>

#include <boost/algorithm/string.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;

void ltr::init_logging()
{
//        Possibility: persist log messages
//        logging::add_file_log("sample.log");
    logging::add_common_attributes();
    logging::add_console_log(std::cout,
                             boost::log::keywords::format = ">> [%TimeStamp%] [%Severity%] %Message%");
}


void ltr::log(vector<string> msg, bool header, vector<const char*> colors, vector<int> sizes){

    if (!colors.empty() && colors.size() < msg.size())
        throw LtrError("Error in ltr::log(): the colors container does not have the same size as the messages container.");

    if (msg.size() != sizes.size()) {
        auto it = std::max_element(msg.begin(), msg.end(),
                                   [](const auto& a, const auto& b) {
                                       return a.size() < b.size();
                                   });
        int max = it->size();
        vector<int> new_sizes(msg.size(), max);
        sizes = new_sizes;
    }

    string head;
    if (header)
        head = log(sizes);

    std::stringstream stream;
    stream << "| ";

    for (int i = 0; i < msg.size(); i++) {
        string start = colors[i];
        string end = start.empty() ? "" : RESET;
        stream << start << std::setw(sizes[i]) << msg[i] << end << " | ";
    }

    LOGGING(info) << stream.str();

    if (header) LOGGING(info) << head;
}

void ltr::log(vector<string> msg, bool header, const char* color, vector<int> sizes) {
    vector<const char*> colors(msg.size(), color);
    log(std::move(msg), header, colors, std::move(sizes));
}

void ltr::log(string msg, log_level type, const char* color, int size) {
    string start = color;
    string end = RESET;
    if (start.empty()) end = "";

    if (size == 0) size = msg.size();
    switch(type) {
        case trace:
            LOGGING(trace) << start << std::setw(size) << msg << end;
            break;
        case info:
            LOGGING(info) << start << std::setw(size) << msg << end;
            break;
        case debug:
            LOGGING(debug) << start << std::setw(size) << msg << end;
            break;
        case warning:
            LOGGING(warning) << start << std::setw(size) << msg << end;
            break;
        case error:
            LOGGING(error) << start << std::setw(size) << msg << end;
            break;
        case fatal:
            LOGGING(fatal) << start << std::setw(size) << msg << end;
            break;
    }
}

string ltr::log(vector<int> sizes){
    std::stringstream stream;
    for(const int& size : sizes)
        stream << "+" << string(size+2, '-');
    stream << "+";
    LOGGING(info) << stream.str();
    return stream.str();
}

const char* ltr::color_score(double value) {
    if (value < 0.3) return RED;
    if (value < 0.6) return YELLOW;
    return GREEN;
}

const char * ltr::color_delta(double value) {
    if (value < 0.0) return RED;
    if (value == 0.0) return "";
    return GREEN;
}

const char * ltr::color_status(const string& status) {
    if (boost::iequals(status, "OK")) return GREEN;
    return RED;
}