/**
 * @file DataSet.hpp
 * @author Marcos Pontes
 * @brief Define a simple DataSet representation
 * @version 0.1
 * @date 2021-03-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef DATA_SET_HPP_
#define DATA_SET_HPP_

//----------------------------------------------------------------//

#include <list>

using std::list;

namespace ltr{
    class RankList;

    /**
     * @brief Initially, a dataset is represented as a linkedlist of RankList objects
     * 
     */
    typedef list<RankList> DataSet; 
};

#endif // DATA_SET_HPP_