#ifndef RANK_LIB_ERROR_HPP_
#define RANK_LIB_ERROR_HPP_

#include <string>
#include <stdexcept>

class RankLibError : public std::runtime_error{
    public:
        RankLibError():std::runtime_error("RankLibError"){}
        RankLibError(std::string message):std::runtime_error(message.c_str()){}
};

#endif