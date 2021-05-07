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

#ifndef LTR_ADARANK_HPP_
#define LTR_ADARANK_HPP_

#include <memory>
#include <unordered_set>

#include "../DataSet.hpp"
#include "../RankList.hpp"
#include "../Ranker.hpp"

using std::unique_ptr;
using std::unordered_set;

namespace ltr {

    /**
     * @brief Weak Ranker used in AdaRank boost algorithm
     * Order items by a single feature
     */
    class WeakRanker : public Learner {
        public:
            /**
             * @brief Construct a new Weak Ranker object
             * 
             * @param featureID 
             */
            explicit WeakRanker(int featureID);
            
            /**
             * @brief Destroy the Weak Ranker object
             * 
             */
            ~WeakRanker();

            /**
             * @brief predict score for a single datapoint
             * 
             * @param dp 
             * @return double 
             */
            double predict(ReadableDataPoint dp) override;

            /**
             * @brief Get the Feature value
             * 
             * @return int 
             */
            int getFeature() const;

        private:
            int featureID;
    };

    class AdaRank : public Ranker {
    public:

        /**
         * Construct a new AdaRank object
         * @param dataset
         * @param scorer
         * @param iter
         * @param tolerance
         * @param maxConsecutive
         * @param features
         * @param validationSet
         */
        AdaRank(DataSet dataset, unique_ptr<MetricScorer> scorer, int iter=50, double tolerance=0.002, int maxConsecutive = 5,
                vector<int> features={}, DataSet validationSet={});

        ~AdaRank();

        /**
         * @brief Learn to rank based on AdaRank.
         * @param verbose indicates to print steps
         */
        void fit(bool verbose);

        /**
         * @brief AdaRank evaluation of a single datapoint object
         * 
         * @param dp 
         * @return double 
         */
        double predict(ReadableDataPoint dp) override;
        
        /**
         * @brief Set the Iter object
         * 
         * @param iter 
         */
        void setIter(int iter);

        /**
         * @brief Set the Tolerance object
         * 
         * @param tolerance 
         */
        void setTolerance(double tolerance);

        /**
         * @brief Set the Consecutive Selections object
         * 
         * @param consecutiveSelections 
         */
        void setConsecutiveSelections(int consecutiveSelections);

        /**
         * @brief Get the number of iterations used in AdaRank
         * @return
         */
        int getIter() const;

        /**
         * @brief Get the number of consecutive selections of ranker in AdaRank
         * @return
         */
        int getConsecutiveSelections() const;

        /**
         * @brief Get the tolerance used in AdaRank
         * @return
         */
        double getTolerance() const;

    protected:

        /**
         * Save json in file
         * @param file
         */
        void saveJSON(std::ofstream& file) override;

        /**
         * Load json from file
         * @param file
         */
        void loadJSON(std::ifstream& file) override;

        /**
         * @brief Learn the data
         * 
         * @param start iteration
         */
        void learn(int start);

        /**
         * @brief Select method of boosting technique
         * 
         * @return WeakRanker
         */
        WeakRanker selectWeakRanker();

        /**
         * @brief Evaluate weak ranker in training samples
         * 
         * @param wk 
         * @return double score
         */
        double evaluateWeakRanker(WeakRanker& wk);

        /**
         * Print header table when starts to fit
         */
        void printHeader();

        /**
         * Print each iter step
         * @param it
         * @param feature
         * @param train_score
         * @param train_improve
         * @param val_score
         * @param val_improve
         * @param status
         */
        void printIter(int it, int feature, double train_score, double train_improve, double val_score, double val_improve, string status);

        /**
         * Print AdaRank results after fit
         */
        void printResults();

        int iter, max_consecutive_selections, consecutive_selections, previous_feature;

        double tolerance, previous_training_score, previous_validation_score;

        vector<double> sample_weights;

        list<double> ranker_weights, best_weights;

        list<WeakRanker> rankers, best_rankers;

        unordered_set<int> used_features;

    private:
        // avoiding
        AdaRank(const AdaRank& rk);
        AdaRank& operator=(const AdaRank& rk);
    };

}

#endif
