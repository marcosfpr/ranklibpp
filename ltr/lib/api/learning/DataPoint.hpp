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

#ifndef DATA_POINT_HPP_
#define DATA_POINT_HPP_

#include <string>

#include "Iterators.hpp"

namespace ltr{

    class DataPointImpl;

    /**
     * @brief A DataPoint is an object to be ranked (Like in RankLib) 
     * @details A DataPoint represent a pair [item, query] extracted
     *  in svm-light format for learning to rank tasks:
     * @code "<LABEL> qid:<QUERY_ID> [<FEATURE_ID: FEATURE_VALUE>]"
     * @endcode
     */
    class DataPoint
    {
    public:
        /**
         * @brief Construct a new DataPoint object based on SVM-Light format string
         * 
         * @param raw : SVM-Light string
         */
        explicit DataPoint(std::string raw = "");

        /**
         * @brief Copy construct  DataPoint object
         * 
         * @param dp other datapoint
         */
        DataPoint(const DataPoint &dp);

        /**
         * @brief Move operator for DataPoint object
         * 
         * @param rhs  other datapoint
         */
        DataPoint(DataPoint&& rhs) noexcept ;

        /**
         * @brief Assign operator for DataPoints
         * 
         * @param dp other datapoint
         * @return DataPoint& 
         */
        DataPoint& operator=(const DataPoint &dp);

        /**
         * @brief Move operator for DataPoints
         * 
         * @param rhs other datapoint
         * @return DataPoint& 
         */
        DataPoint& operator=(DataPoint&& rhs) noexcept ;

        /**
         * @brief Destroy the DataPoint object
         * 
         */
        ~DataPoint();

        /**
         * @brief Return string representation of a DataPoint in SVM-Light format
         * 
         * @return std::string 
         */
        std::string toString() const;

        /**
         * @brief Update the id of DataPoint
         * 
         * @param id  new item id
         */
        void setID(std::string id);

        /**
         * @brief Get the id of DataPoint
         * 
         * @return std::string 
         */
        std::string getID() const;

        /**
         * @brief Get the number of features used
         * 
         * @return int 
         */
        int getFeatureCount() const;

        /**
         * @brief Get the Label of this DataPoint
         * 
         * @return float 
         */
        float getLabel() const;

        /**
         * @brief Set the Label value for this DataPoint
         * 
         * @param label new label value
         */
        void setLabel(float lbl);

        /**
         * @brief Get the Description of this DataPointImpl
         * @note In SVM-Light, description is started with "#" keyword
         * 
         * @return std::string 
         */
        std::string getDescription() const;

        /**
         * @brief Set the Description value (sometimes indicates the document name)
         * 
         * @param description 
         */
        void setDescription(std::string desc);

        /**
         * @brief Get the Feature Value object
         * 
         * @param featureID 
         * @return float 
         */
        float getFeatureValue(int featureID) const;

        /**
         * @brief Set the Feature Value object
         * 
         * @param featureID 
         * @param featureValue 
         */
        void setFeatureValue(int featureID, float featureValue);

        /**
         * @brief Gets the value of all features as a dense array of feature values.
         * 
         * @return container of feature values
         */
        FeaturesContainer getFeatureVector() const;

        /**
         * @brief Sets the value of all features with the provided dense array of feature values
         * 
         * @param features container of features values
         */
        void setFeatureVector(FeaturesContainer features);

    private:
        DataPointImpl *p_impl;
    };

};

#endif // DATA_POINT_HPP_