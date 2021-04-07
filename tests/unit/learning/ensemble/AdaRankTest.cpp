#include <ltr.hpp>

#include <gtest/gtest.h>

#include <memory>
#include <cstdlib>

using ltr::Ranker;
using ltr::DataSet;
using ltr::MAPScorer;
using ltr::AdaRank;

class AdaRankTest : public ::testing::Test {

protected:
    AdaRank * ranker;
    DataSet training_samples;
    AdaRankTest() = default;

    virtual ~AdaRankTest() = default;

    virtual void SetUp(){
        string base_path = std::getenv("OHSUMED");
        DataSet training_samples = ltr::load_svmlight(base_path + "/Data/All/OHSUMED.txt");
        ranker = new AdaRank(std::move(training_samples), std::make_unique<MAPScorer>());
    }

    virtual void TearDown(){
        delete ranker;
    }

};

TEST_F(AdaRankTest, check_weak_ranker) {
    ltr::WeakRanker wk(1);

    ltr::ReadableDataPoint rd = std::make_shared<ltr::DataPoint>("0 qid:10 1:0.2 2:1.3 3:9.2 # doc1 2");

    ASSERT_FLOAT_EQ(0.2, wk.predict(rd));
    ASSERT_EQ(1, wk.getFeature());

}

TEST_F(AdaRankTest, get_set) {

    ranker->setIter(10);
    ranker->setConsecutiveSelections(2);
    ranker->setTolerance(0.001);

    ASSERT_EQ(10, ranker->getIter());
    ASSERT_EQ(2, ranker->getConsecutiveSelections());
    ASSERT_FLOAT_EQ(0.001, ranker->getTolerance());
    ASSERT_STREQ("AdaRank", ranker->name().c_str());

    map<string, double> params_to_set = {{"iter", 20}, {"consecutiveSelections", 30}, {"tolerance", 0.02}};
    ranker->setParameters(params_to_set);
    ASSERT_EQ(20, ranker->getIter());
    ASSERT_EQ(30, ranker->getConsecutiveSelections());
    ASSERT_FLOAT_EQ(0.02, ranker->getTolerance());

    auto get_params = ranker->getParameters();
    ASSERT_EQ(get_params, params_to_set);
}


