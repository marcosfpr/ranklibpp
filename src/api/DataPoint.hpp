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


class DataPointImpl;

/**
 * @brief A DataPoint is an object to be ranked (Like in RankLib) 
 * 
 */
class DataPoint {
public:
	
    /**
     * @brief Construct a new Data Point object
     * 
     * @param raw raw text that represents all features
     */
    DataPoint(std::string raw="");

    /**
     * @brief Construct a new Data Point object
     * 
     * @param dp other datapoint
     */
    DataPoint(const DataPoint& dp);

    /**
     * @brief Assign operator for DataPoints
     * 
     * @param dp other datapoint
     * @return DataPoint& 
     */
    DataPoint& operator=(const DataPoint& dp);

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
    std::string toString();


    /**
     * @brief Update the id value
     * 
     * @param id 
     */
    void  setID(std::string id);
    
    /**
     * @brief Get the id value
     * 
     * @return std::string 
     */
    std::string  getID();

    /**
     * @brief Get the Feature Count
     * 
     * @return int 
     */
    int getFeatureCount();

    /**
     * @brief Get the Label
     * 
     * @return float 
     */
    float getLabel();
	
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
	std::string getDescription();
	
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
	double getCached();
	
    /**
     * @brief 
     * 
     */
	void resetCached();

    /**
     * @brief Get the Feature Value object
     * 
     * @param featureID 
     * @return float 
     */
    float getFeatureValue(int featureID);


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
    std::vector<float> getFeatureVector();


    /**
     * @brief Sets the value of all features with the provided dense array of feature values
     * 
     * @param featureVector 
     */
    void setFeatureVector(std::vector<float> featureVector);


    friend std::ostream& operator<<(std::ostream& os, const DataPoint& dp);

private:

    DataPointImpl* p_impl;

};


#endif // DATA_POINT_HPP_