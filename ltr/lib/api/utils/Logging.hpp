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
#ifndef LTR_LOGGING_HPP_
#define LTR_LOGGING_HPP_

#include <vector>
#include <string>

using std::string;
using std::vector;

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

namespace ltr {

    void init_logging();

    enum log_level
    {
        info,
        debug,
        warning,
        error,
        critical
    };

    /**
     * Color of score in range 0-1
     * @param value
     * @return
     */
    const char* color_score(double value);

    /**
     * Color of delta score
     * @param delta
     * @return
     */
    const char* color_delta(double delta);

    /**
     * Color of status string
     * @param status
     * @return
     */
    const char* color_status(const string& status);

    /**
     * Log a set of messages into screen;
     * @param msg
     * @param header
     * @param colors
     * @param sizes
     */
    void log(vector<string> msg, bool header=false, vector<const char*> colors = {}, vector<int> sizes = {});

    /**
     * Log a set of messages with single color
     * @param msg
     * @param header
     * @param color
     * @param sizes
     */
    void log(vector<string> msg, bool header=false, const char* color="", vector<int> sizes = {});

    /**
     * Log footer of table
     * @param color
     * @param sizes
     * @return string footer line
     */
    string log(vector<int> sizes);

    /**
     * @brief Log a set of messages into screen;
     *
     * @param msg
     * @param type
     * @param size
     */
    void log(string msg, log_level type, const char* color="", int size=0);

}; 

#endif