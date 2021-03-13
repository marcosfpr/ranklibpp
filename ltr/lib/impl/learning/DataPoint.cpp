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

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <utility>
#include <sstream>
#include <iomanip>

#include "../../api/learning/DataPoint.hpp"
#include "../../api/LtrError.hpp"

#include "boost/algorithm/string.hpp"

#define NaN -1000.00

using std::move;
using std::string;
using std::vector;

using namespace ltr;

#define MAX_FEATURES 51
#define FEATURE_RESIZE_STEP 10

class ltr::DataPointImpl
{
public:
    DataPointImpl(string raw = "")
    {
        init(move(raw));
    }

    DataPointImpl(const DataPointImpl &dp)
    {
        initFrom(dp);
    }

    ~DataPointImpl()
    {
        freePointers();
    }

    string toString()
    {
        string output = std::to_string((int)label) + " " + id_ + " ";
        for (int i = 1; i < feature_values.size(); i++)
        {
            float fVal = getFeatureValue(i);
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << fVal;
            if (fVal != NaN)
            {
                output += std::to_string(i) + ":" + ss.str() + (i == feature_values.size() - 1 ? "" : " ");
            }
        }
        output += " # " + description;
        return output;
    }

    void setID(string id)
    {
        this->id_ = id;
    }

    string getID()
    {
        return this->id_;
    }

    int getFeatureCount()
    {
        return feature_count;
    }

    float getLabel()
    {
        return this->label;
    }

    void setLabel(float label)
    {
        this->label = label;
    }

    string getDescription()
    {
        return this->description;
    }

    void setDescription(string description)
    {
        this->description = description;
    }

    float getFeatureValue(int featureID)
    {
        if (featureID <= 0 || featureID > this->feature_values.size())
            throw new LtrError("Error in DataPoint::getFeatureValue(): requesting unspecified feature, fid=" + std::to_string(featureID));
        return this->feature_values[featureID];
    }

    void setFeatureValue(int featureID, float featureValue)
    {
        if (featureID <= 0 || featureID > this->feature_values.size())
            throw new LtrError("Error in DataPoint::setFeatureValue(): requesting unspecified feature, fid=" + std::to_string(featureID));
        this->feature_values[featureID] = featureValue;
    }

    vector<float> getFeatureVector()
    {
        return this->feature_values;
    }

    void setFeatureVector(vector<float> featureVector)
    {
        this->feature_count = featureVector.size() - 1;
        this->feature_values = move(featureVector);
    }

    void init(string raw = "")
    {
        this->label = 0.0;
        this->known_features = 0;
        this->feature_values.resize(max_feature, NaN);
        if (!raw.empty())
            parse(move(raw));
    }

    void initFrom(const DataPointImpl &dp)
    {
        this->label = dp.label;
        this->description = dp.description;
        this->id_ = dp.id_;
        this->known_features = dp.known_features;
        this->feature_values = dp.feature_values;
    }

    void freePointers() {}

    static int max_feature;
    static int feature_increase;

protected:
    void getKeyValueFeaturePair(std::pair<string, string> &keyValue, string feature)
    {
        vector<string> tokens;
        boost::split(tokens, feature, boost::is_any_of(":"));
        keyValue = std::make_pair(tokens[0], tokens[1]);
    }

    void parse(string raw)
    {
        std::fill(feature_values.begin(), feature_values.end(), NaN);
        int last_feature = -1;
        try
        {
            std::size_t idx = raw.find("#");
            if (idx != string::npos)
            {
                this->description = raw.substr(idx+1);
                raw = raw.substr(0, idx); // raw text without comments
                boost::trim(raw);
                boost::trim(this->description);
            }

            vector<string> tokens;
            boost::split(tokens, raw, boost::is_any_of(" "));

            this->label = std::stof(tokens[0]);

            if (label < 0)
                throw new LtrError("Relevance label cannot be negative.");

            this->id_ = tokens[1];

            std::pair<string, string> key_value;
            for (int i = 2; i < tokens.size(); i++)
            {
                this->known_features++;
                getKeyValueFeaturePair(key_value, tokens[i]);

                int fid = std::stoi(key_value.first);
                if (fid <= 0)
                    throw new LtrError("Cannot use feature numbering less than or equal to zero. Start your features at 1.");
                if (fid >= max_feature)
                {
                    while (fid >= max_feature)
                    {
                        max_feature += feature_increase;
                    }
                    this->feature_values.resize(max_feature, NaN);
                }
                this->feature_values[fid] = std::stof(key_value.second);

                if (fid > feature_count)
                    feature_count = fid; // max_feature for entire dataset

                if (fid > last_feature)
                {
                    last_feature = fid; // max_feature for datapoint
                }
            }
        }
        catch (std::exception e)
        {
            throw new LtrError("Error in DataPoint::parse()");
        }
    }

    static int feature_count;
    int known_features;
    float label;
    string id_, description;
    vector<float> feature_values;
};

int DataPointImpl::max_feature = MAX_FEATURES;
int DataPointImpl::feature_increase = FEATURE_RESIZE_STEP;
int DataPointImpl::feature_count = 0;

DataPoint::DataPoint(string raw)
{
    this->p_impl = new DataPointImpl(std::move(raw));
}

DataPoint::DataPoint(const DataPoint &dp)
{
    this->p_impl = new DataPointImpl(*dp.p_impl);
}

DataPoint::DataPoint(DataPoint &&rhs)
{
    this->p_impl = rhs.p_impl;
    rhs.p_impl = nullptr;
}

DataPoint &DataPoint::operator=(const DataPoint &dp)
{
    p_impl->initFrom(*dp.p_impl);
    return *this;
}

DataPoint &DataPoint::operator=(DataPoint &&rhs)
{
    if (this != &rhs)
    {
        delete p_impl;
        p_impl = rhs.p_impl;
        rhs.p_impl = nullptr;
    }
    return *this;
}

DataPoint::~DataPoint()
{
    delete p_impl;
}

void DataPoint::setID(string id)
{
    p_impl->setID(id);
}

string DataPoint::getID() const
{
    return p_impl->getID();
}

int DataPoint::getFeatureCount() const
{
    return p_impl->getFeatureCount();
}

float DataPoint::getLabel() const
{
    return p_impl->getLabel();
}

void DataPoint::setLabel(float label)
{
    p_impl->setLabel(label);
}

string DataPoint::getDescription() const
{
    return p_impl->getDescription();
}

void DataPoint::setDescription(string description)
{
    p_impl->setDescription(description);
}

float DataPoint::getFeatureValue(int featureID) const
{
    return p_impl->getFeatureValue(featureID);
}

void DataPoint::setFeatureValue(int featureID, float featureValue)
{
    p_impl->setFeatureValue(featureID, featureValue);
}

vector<float> DataPoint::getFeatureVector() const
{
    return p_impl->getFeatureVector();
}

void DataPoint::setFeatureVector(vector<float> featureVector)
{
    p_impl->setFeatureVector(move(featureVector));
}

string DataPoint::toString() const
{
    return p_impl->toString();
}