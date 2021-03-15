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

#ifndef RANKER_HPP_
#define RANKER_HPP_

#include <list>
#include <vector>
#include <string>
#include <memory>

#include "DataSet.hpp"
#include "RankList.hpp"

using std::unique_ptr;
using std::string;
using std::list;
using std::vector;

namespace ltr {

    class RankerImpl;
    class MetricScorer;
    
    /**
     * @brief Generic Ranker class
     * 
     */
    class Ranker{
        public:

            /**
             * @brief Learn method for some learning algorithm.
             * 
             */
            virtual void fit();

            /**
             * @brief Evaluation of a single datapoint object
             * 
             * @param dp 
             * @return double 
             */
            virtual double predict(ReadableDataPoint dp);

            /**
             * @brief String representation of ranker
             * 
             * @return string 
             */
            virtual string toString();

            /**
             * @brief String representation of model
             * 
             * @return string 
             */
            virtual string model();

            /**
             * @brief Load model from string
             * 
             * @param model 
             */
            virtual void loadString(string model);

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
             * @brief Construct a new Ranker object
             * 
             * @param dataset 
             * @param features 
             * @param scorer 
             */
            Ranker(DataSet dataset, unique_ptr<MetricScorer> scorer, vector<int> features={});

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
            void setScorer(unique_ptr<MetricScorer> scorer);

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
             * @brief Save model in file
             * 
             * @param fileToSave 
             */
            void save(string fileToSave);
        
        private:
            
            RankerImpl* p_impl;

    };

};

#endif // !RANKER_HPP_