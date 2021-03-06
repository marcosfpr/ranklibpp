/**
 * @file Ranker.hpp
 * @author Marcos Pontes
 * @brief Ranker generic class
 * @version 0.1
 * @date 2021-03-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef RANKER_HPP_
#define RANKER_HPP_

#include <list>
#include <vector>
#include <string>
#include <memory>

using std::string;
using std::list;
using std::vector;

namespace ranklib {

    class RankList;
    class DataPoint;
    class MetricScorer;
    
    class RankerImpl;

    class Ranker {
    public:

        /**
         * @brief Initialization of Ranking algorithm.
         * 
         */
        virtual void init() = 0;

        /**
         * @brief Learn method for some learning algorithm.
         * 
         */
        virtual void learn() = 0;

        /**
         * @brief Evaluation of a single datapoint object
         * 
         * @param dp 
         * @return double 
         */
        virtual double eval(ReadableDataPoint dp) = 0;

        /**
         * @brief String representation of ranker
         * 
         * @return string 
         */
        virtual string toString() = 0;

        /**
         * @brief String representation of model
         * 
         * @return string 
         */
        virtual string model() = 0;

        /**
         * @brief Load model from string
         * 
         * @param model 
         */
        virtual void loadString(string model) = 0;

        /**
         * @brief String name of model
         * 
         * @return string 
         */
        virtual string name() = 0;

        /**
         * @brief Logging model stats
         * 
         */
        virtual void print() = 0;


        /**
         * @brief Construct a new Ranker object
         * 
         * @param dataset 
         * @param features 
         * @param scorer 
         */
        Ranker(DataSet dataset, vector<int> features, MetricScorer* scorer);

        /**
         * @brief Destroy the Ranker object
         * 
         */
        ~Ranker();

        /**
         * @brief Construct a new Ranker object
         * 
         * @param rk 
         */
        Ranker(const Ranker& rk);

        /**
         * @brief Assign operator for Rankers
         * 
         * @param rk other ranker
         * @return Ranker& 
         */
        Ranker& operator=(const Ranker& rk);

        /**
         * @brief Set the Training Set of Ranker
         * 
         * @param dataset 
         */
        void setTrainingSet(DataSet dataset);

        /**
         * @brief Set the Features for Ranker
         * 
         * @param features 
         */
        void setFeatures(vector<int> features);

        /**
         * @brief Set the Validation Set for Ranker
         * 
         * @param samples 
         */
        void setValidationSet(DataSet dataset);

        /**
         * @brief Set the Scorer wich will be used for Ranker
         * 
         * @param scorer 
         */
        void setScorer(MetricScorer* scorer);

        /**
         * @brief Get the Training Score
         * 
         * @return double 
         */
        double getTrainingScore();

        /**
         * @brief Get the Validation Score
         * 
         * @return double 
         */
        double getValidationScore();

        /**
         * @brief Get the used Features
         * 
         * @return vector<int> 
         */
        vector<int> getFeatures();

        /**
         * @brief Perform ranking in samples
         * 
         * @param l 
         */
        void rank(DataSet& l);

        /**
         * @brief Perform ranking in one sample
         * 
         * @param l 
         */
        void rank(RankList& rl);
        
        /**
         * @brief Save model in file
         * 
         * @param fileToSave 
         */
        void save(string fileToSave);

    private:
        RankerImpl * p_impl;

    };

};

#endif // !RANKER_HPP_