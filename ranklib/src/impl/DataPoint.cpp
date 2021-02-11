/**
 * @file DataPoint.cpp
 * @author Marcos Pontes
 * @brief Impl of a DataPoint
 * @version 0.1
 * @date 2021-02-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <utility>

#include  "../api/DataPoint.hpp"
#include  "../api/RankLibError.hpp"

#include "boost/algorithm/string.hpp"

#define NaN -1000.00

using std::move;
using std::string;
using std::vector;

class DataPointImpl{
    public:
	

    DataPointImpl(string raw=""){
        init(move(raw));
    }


    DataPointImpl(const DataPointImpl& dp){
        initFrom(dp);
    }


    ~DataPointImpl(){
        freePointers();
    }

    string toString(){
        string output = std::to_string((int)label) + " " + id_ + " ";
        for(int i=1; i<feature_values.size(); i++){
            float fVal = getFeatureValue(i);
            if(fVal != NaN){
                output += std::to_string(i) + ":" + std::to_string(fVal) + (i==feature_values.size()-1 ? "" : " ");
            }
        }
        output += " " + description;
        return output;
    }

    void  setID(string id){
        this->id_ = id;
    }

    string  getID(){
        return this->id_;
    }


    int getFeatureCount() {
        return feature_count;
    }


    float getLabel() {
        return this->label;
    }
	

    void setLabel(float label) {
        this->label = label;
    }
	

    string getDescription() {
        return this->description;
    }
	

    void setDescription(string description) {
        this->description = description;
    }

	 void setCached(double c){
         this->cached = c;
     }
	

	 double getCached(){
         return this->cached;
     }
	
    
	 void resetCached() {
         this->cached = -1000;
     }


     float getFeatureValue(int featureID) {
        if(featureID <= 0 || featureID > this->feature_values.size())
            throw new RankLibError("Error in DataPoint::getFeatureValue(): requesting unspecified feature, fid=" + featureID);
        return this->feature_values[featureID];
     }


     void setFeatureValue(int featureID, float featureValue) {
         if(featureID <= 0 || featureID > this->feature_values.size())
            throw new RankLibError("Error in DataPoint::setFeatureValue(): requesting unspecified feature, fid=" + featureID);
        this->feature_values[featureID] = featureValue;
     }

     vector<float> getFeatureVector(){
         return this->feature_values;
     }


     void setFeatureVector(vector<float> featureVector){
         this->feature_values = move(featureVector);
     }


    friend std::ostream& operator<<(std::ostream& os, const DataPoint& dp);
    
    void init(string raw=""){
        this->label = 0.0;
        this->cached = -1;
        this->known_features = 0;
        if(!raw.empty())
            parse(move(raw));
    }

    void initFrom(const DataPointImpl& dp){
        this->label = dp.label;
        this->cached = dp.cached;
        this->description = dp.description;
        this->id_ = dp.id_;
        this->known_features = dp.known_features;
        this->feature_values = dp.feature_values;
    }
    
    void freePointers(){}

    static int max_feature;
    static int feature_increase;

    protected:

        void getKeyValueFeaturePair(std::pair<string, string>& keyValue, string feature){
            vector<string> tokens;
            boost::split(tokens, feature, boost::is_any_of(":"));
            keyValue = std::make_pair(tokens[0], tokens[1]);
        }

        void parse(string raw){
            this->feature_values.resize(max_feature);
            std::fill(feature_values.begin(), feature_values.end(), NaN);
            int last_feature = -1;
            try{
                std::size_t idx = raw.find("#");
                if(idx != string::npos){
                    this->description = raw.substr(idx);
                    raw = raw.substr(0, idx); // raw text without comments
                    boost::trim(raw);
                }

                vector<string> tokens;
                boost::split(tokens, raw, boost::is_any_of(" "));

                this->label = std::stof(tokens[0]);

                if(label < 0)
                    throw new RankLibError("Relevance label cannot be negative. System will now exit");
                
                this->id_ = tokens[1];

                std::pair<string, string> key_value;
                for(int i = 2; i < tokens.size(); i++){
                    this->known_features++;
                    getKeyValueFeaturePair(key_value, tokens[i]);

                    int fid = std::stoi(key_value.first);
                    if(fid <= 0) throw new RankLibError("Cannot use feature numbering less than or equal to zero. Start your features at 1.");
                    if(fid >= max_feature){
                        while(fid >= max_feature){
                            max_feature +=  feature_increase;
                        }
                        this->feature_values.resize(max_feature, NaN);
                    }
                    this->feature_values[fid] = std::stof(key_value.second);

                    if(fid > feature_count)
                        feature_count = fid; // max_feature for entire dataset
                    
                    if(fid > last_feature){
                        last_feature = fid; // max_feature for datapoint
                    }
                }

            }
            catch(std::exception e){
                throw new RankLibError("Error in DataPoint::parse()");
            }
        }

        static int feature_count;
        int known_features;
        float label;
        double cached;
        string id_, description;
        vector<float> feature_values;     

};

int DataPointImpl::max_feature = 51;
int DataPointImpl::feature_increase = 10;
int DataPointImpl::feature_count = 0;


DataPoint::DataPoint(string raw){
    this->p_impl = new DataPointImpl(std::move(raw));
}


DataPoint::DataPoint(const DataPoint& dp){
    this->p_impl = new DataPointImpl(*dp.p_impl);
}

DataPoint::DataPoint(DataPoint&& rhs){
    this->p_impl = rhs.p_impl;
    rhs.p_impl = nullptr;
}

DataPoint& DataPoint::operator=(const DataPoint& dp){
    p_impl->initFrom(*dp.p_impl);
    return *this;
}

DataPoint& DataPoint::operator=(DataPoint&& rhs){
    if(this != &rhs)
    {
        delete p_impl;
        p_impl = rhs.p_impl;
        rhs.p_impl = nullptr;
    }
    return *this;
}

DataPoint::~DataPoint(){
    delete p_impl;
}


void DataPoint::setID(string id) {
    p_impl->setID(id);
}


 string  DataPoint::getID() {
    return p_impl->getID();
 }

 int DataPoint::getFeatureCount() {
    return p_impl->getFeatureCount();
 }


 float DataPoint::getLabel(){
    return p_impl->getLabel();
 }


 void DataPoint::setLabel(float label){
    p_impl->setLabel(label);
 }

 string DataPoint::getDescription(){
    return p_impl->getDescription();
 }

 void DataPoint::setDescription(string description){
    p_impl->setDescription(description);
 }

 void DataPoint::setCached(double c){
    p_impl->setCached(c);
 }

 double DataPoint::getCached(){
    return p_impl->getCached();
 }

 void DataPoint::resetCached(){
    p_impl->resetCached();
 }

 float DataPoint::getFeatureValue(int featureID){
    return p_impl->getFeatureValue(featureID);
 }

 void DataPoint::setFeatureValue(int featureID, float featureValue){
    p_impl->setFeatureValue(featureID, featureValue);
 }

 vector<float> DataPoint::getFeatureVector(){
    return p_impl->getFeatureVector();
 }

 void DataPoint::setFeatureVector(vector<float> featureVector){
    p_impl->setFeatureVector(move(featureVector));
 }


string DataPoint::toString(){
    return p_impl->toString();
}