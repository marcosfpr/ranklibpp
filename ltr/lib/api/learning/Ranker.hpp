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
#include <map>
#include <string>
#include <memory>

#include "Learner.hpp"
#include "../utils/Logging.hpp"

using std::unique_ptr;
using std::string;
using std::list;
using std::vector;
using std::map;

namespace ltr {

    class MetricScorer;
    
    /**
     * @brief Generic Ranker class
     * 
     */
    class Ranker : public Learner{
        public:

            /**
             * @brief Construct a new Ranker object
             * 
             * @param dataset 
             * @param features 
             * @param scorer 
             * @param validationSet
             */
            Ranker(DataSet dataset, unique_ptr<MetricScorer> scorer, vector<int> features={}, DataSet validationSet={});

            /**
             * @brief Destroy the Ranker object
             * 
             */
            ~Ranker();

            /**
             * @brief Learn method for some learning algorithm.
             * @param verbose print steps of learn
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
             * @brief map of parameters
             * 
             * @return map <name of parameter, value> 
             */
            virtual map<string, double> getParameters();

            /**
             * @brief map of parameters
             * @param map <name of parameter, value>
             */
            virtual void setParameters(map<string, double> parameters);

            /**
             * @brief Return the name of the LTR Method.
             * 
             * @return const string 
             */
            virtual string name() const;
            
            /**
             * @brief Set the Training Set of Ranker
             * 
             * @param dataset 
             */
            void setTrainingSet(DataSet dataset);

            /**
             * @brief Set the Features for Ranker
             * 
             * @param ft  new features vector
             */
            void setFeatures(vector<int> ft);

            /**
             * @brief Set the Validation Set for Ranker
             * 
             * @param samples 
             */
            void setValidationSet(DataSet dataset);

            /**
             * @brief Set the Scorer wich will be used for Ranker
             * 
             * @param scr
             */
            void setScorer(unique_ptr<MetricScorer> scr);

            /**
             * @brief Get the Training Score
             * 
             * @return double 
             */
            virtual double getTrainingScore() const;

            /**
             * @brief Get the Validation Score
             * 
             * @return double 
             */
            double getValidationScore() const;

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
            void save(const string& fileToSave);

            /**
             * @brief Lodel model from file
             * 
             * @param fileToLoad 
             */
            void load(const string& fileToLoad);

        protected:
            /**
             * @brief Extract all features used on training samples.
             * 
             */
            void extractFeatures();

            /**
             * @brief Log a set of messages into screen;
             * 
             * @param msg 
             * @param type
             * @param size
             */
            void log(vector<string> msg, log_level type, vector<int> sizes = {}) const;

            /**
             * @brief Log a set of messages into screen;
             *
             * @param msg
             * @param type
             * @param size
             */
            void log(string msg, log_level type, int size=0) const;

            DataSet training_samples, validation_samples;

            vector<int> features;
            
            unique_ptr<MetricScorer> scorer;

            double score_training, score_validation;

            bool verbose;

      private:

            // avoiding operators 
            
            Ranker(const Ranker& rk);

            Ranker& operator=(const Ranker& rk);
    };

}

#endif // !RANKER_HPP_