/**
 * @file AdaRank.hpp
 * @author Marcos Pontes
 * @brief Listwise boost algorithm based on AdaBoost
 * @version 0.1
 * @date 2021-03-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef ADARANK_HPP_
#define ADARANK_HPP_

#include "../Ranker.hpp"

namespace ltr{

    class AdaRankImpl;

    /**
     * @brief Listwise boost algorithm based on AdaBoost
     * 
     */
    class AdaRank : public Ranker{
        public:
             /**
             * @brief Construct a new Ranker object
             * 
             * @param dataset 
             * @param features 
             * @param scorer 
             */
            AdaRank(DataSet dataset, vector<int> features, unique_ptr<MetricScorer> scorer,
                    int nIteration=30, double tolerance=0.002, bool enqueue=true, int maxSelCount=5);

            /**
             * @brief Destroy the AdaRank object
             * 
             */
            ~AdaRank();

            /**
             * @brief Construct a new AdaRank object
             * 
             * @param rk 
             */
            AdaRank(const AdaRank& rk);

            /**
             * @brief Assign operator for AdaRank
             * 
             * @param rk other ranker
             * @return Ranker& 
             */
            AdaRank& operator=(const AdaRank& rk);


            /**
             * @brief Initialization of Ranking algorithm.
             * 
             */
            void start() override;

            /**
             * @brief Learn method for some learning algorithm.
             * 
             */
            void learn() override;

            /**
             * @brief Evaluation of a single datapoint object
             * 
             * @param dp 
             * @return double 
             */
            double eval(ReadableDataPoint dp) override;

            /**
             * @brief String representation of ranker
             * 
             * @return string 
             */
            string toString() override;

            /**
             * @brief String representation of model
             * 
             * @return string 
             */
            string model() override;

            /**
             * @brief Load model from string
             * 
             * @param model 
             */
            void loadString(string model) override;

            /**
             * @brief String name of model
             * 
             * @return string 
             */
            string name() override;

            /**
             * @brief Logging model stats
             * 
             */
            void print() override;

            /**
             * @brief Set the number of Iterations
             * 
             * @param nIteration 
             */
            void setIterations(int nIteration);

            /**
             * @brief Get the number of Iterations
             * 
             * @return int 
             */
            int getIterations();

            /**
             * @brief Set the Tolerance
             * 
             * @param tolerance 
             */
            void setTolerance(double tolerance);

            /**
             * @brief Get the Tolerance
             * 
             * @return double 
             */
            double getTolerance();

            /**
             * @brief Set if Enqueue
             * 
             * @param enqueue 
             */
            void setEnqueue(bool enqueue);
            
            /**
             * @brief Get the Enqueue value
             * 
             * @return true 
             * @return false 
             */
            bool getEnqueue();

            /**
             * @brief Set the the max number of times a feature can be selected consecutively before being removed
             * 
             * @param maxSelCount 
             */
            void setMaxSelCount(int maxSelCount);

            /**
             * @brief Get the the max number of times a feature can be selected consecutively before being removed
             * 
             * @return int 
             */
            int getMaxSelCount();

        private:
            AdaRankImpl* p_impl;
    };
};

#endif // ADARANK_HPP_