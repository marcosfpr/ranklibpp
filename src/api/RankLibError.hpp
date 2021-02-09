/**
 * @file RankLibError.hpp
 * @author your name (you@domain.com)
 * @brief RankLib generic error class.
 * @version 0.1
 * @date 2021-02-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef RANK_LIB_ERROR_HPP_
#define RANK_LIB_ERROR_HPP_

#include <string>
#include <stdexcept>

/**
 * @brief Error occurrence in Ranklib core.my_cool_project
 * 
 */
class RankLibError : public std::runtime_error{
    public:
        RankLibError():std::runtime_error("RankLibError"){}
        RankLibError(std::string message):std::runtime_error(message.c_str()){}
};

#endif