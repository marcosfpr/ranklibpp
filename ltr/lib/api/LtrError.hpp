/**
 * @file LtrError.hpp
 * @author Marcos Pontes
 * @brief LTR++ generic error class.
 * @version 0.1
 * @date 2021-02-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef LTR_ERROR_HPP_
#define LTR_ERROR_HPP_

#include <string>
#include <stdexcept>

namespace ltr{
        
    /**
     * @brief Error occurrence in LtrError core.my_cool_project
     * 
     */
    class LtrError : public std::runtime_error{
        public:
            LtrError():std::runtime_error("LtrError"){}
            LtrError(std::string message):std::runtime_error(message.c_str()){}
    };
};

#endif