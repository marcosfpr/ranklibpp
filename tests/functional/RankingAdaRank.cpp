#include <ltr.hpp>

#include <gtest/gtest.h>

#include <memory>
#include <cstdlib>

using ltr::Ranker;
using ltr::DataSet;
using ltr::MAPScorer;
using ltr::AdaRank;

class RankingAdaRank : public ::testing::Test {

protected:
    AdaRank * ranker;
    DataSet training_samples;

    RankingAdaRank() = default;
    virtual ~RankingAdaRank() = default;

    virtual void SetUp(){
        string base_path = std::getenv("OHSUMED");
        DataSet training_samples = ltr::load_svmlight(base_path + "/Data/All/OHSUMED.txt");
        ranker = new AdaRank(std::move(training_samples), std::make_unique<MAPScorer>());
    }

    virtual void TearDown(){
        delete ranker;
    }
};

TEST_F(RankingAdaRank, adarank_map_ohsumed) {
    /**
     * Fitting OHSUMED training samples with AdaRank based on MAP Score
     */
    ranker->fit(false);
    ranker->setIter(50);
    ranker->setConsecutiveSelections(3);
    ranker->setTolerance(0.003);

    // in the benchmark, the average MAP is something higher than 44%

    LOGGING(info) << ranker->getTrainingScore();

    EXPECT_TRUE(ranker->getTrainingScore() > 0.44);
}