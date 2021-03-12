/**
 * @file DataPoint.hpp
 * @author Marcos Pontes
 * @brief A DataPoint is an object to be ranked (Like in RankLib) 
 * @version 0.1
 * @date 2021-02-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef DATA_POINT_HPP_
#define DATA_POINT_HPP_
#include <vector>
#include <string>
#include <iostream>


namespace ltr{
    
    class DataPointImpl;

    /**
     * @brief A DataPoint is an object to be ranked (Like in RankLib) 
     * 
     */
    class DataPoint
    {
    public:
        /**
         * @brief Construct a new Data Point object
         * 
         * @param raw raw text that represents all features
         */
        DataPoint(std::string raw = "");

        /**
         * @brief Construct a new Data Point object
         * 
         * @param dp other datapoint
         */
        DataPoint(const DataPoint &dp);

        /**
         * @brief Construct a new Data Point object
         * 
         * @param rhs 
         */
        DataPoint(DataPoint&& rhs);

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
         * @param rhs 
         * @return DataPoint& 
         */
        DataPoint& operator=(DataPoint&& rhs);

        /**
         * @brief Destroy the DataPoint object
         * 
         */
        ~DataPoint();

        /**
         * @brief Return string representation of a datapoint
         * 
         * @return std::string 
         */
        std::string toString() const;

        /**
         * @brief Update the id value
         * 
         * @param id 
         */
        void setID(std::string id);

        /**
         * @brief Get the id value
         * 
         * @return std::string 
         */
        std::string getID() const;

        /**
         * @brief Get the Feature Count
         * 
         * @return int 
         */
        int getFeatureCount() const;

        /**
         * @brief Get the Label
         * 
         * @return float 
         */
        float getLabel() const;

        /**
         * @brief Set the Label
         * 
         * @param label 
         */
        void setLabel(float label);

        /**
         * @brief Get the Description
         * 
         * @return std::string 
         */
        std::string getDescription() const;

        /**
         * @brief Set the Description
         * 
         * @param description 
         */
        void setDescription(std::string description);

        /**
         * @brief Set the Cached value
         * 
         * @param c 
         */
        void setCached(double c);

        /**
         * @brief Get the Cached value
         * 
         * @return double 
         */
        double getCached() const;

        /**
         * @brief Reset cached value
         * 
         */
        void resetCached();

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
         * @return std::vector<float> 
         */
        std::vector<float> getFeatureVector() const;

        /**
         * @brief Sets the value of all features with the provided dense array of feature values
         * 
         * @param featureVector 
         */
        void setFeatureVector(std::vector<float> featureVector);

    private:
        DataPointImpl *p_impl;
    };

};

#endif // DATA_POINT_HPP_