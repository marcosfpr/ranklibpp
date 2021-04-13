#include <ltr.hpp>

#include <gtest/gtest.h>
#include <experimental/filesystem>

#include <memory>
#include <cstdlib>

using namespace ltr;
namespace fs = std::experimental::filesystem;

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

}

TEST_F(AdaRankTest, save) {

    ranker->setTolerance(0.2);
    ranker->setConsecutiveSelections(100);
    ranker->setIter(150);

    string file_path = "./adarank.json";
    ranker->save(file_path);

    fs::path path = fs::path(file_path.c_str());

    ASSERT_TRUE(fs::exists(path));

    string expected = "AdaRank";

    AdaRank other({}, std::make_unique<MAPScorer>(), {});

    other.load("./adarank.json");

    ASSERT_FLOAT_EQ(ranker->getTolerance(), other.getTolerance());
    ASSERT_EQ(ranker->getIter(), other.getIter());
    ASSERT_EQ(ranker->getConsecutiveSelections(), other.getConsecutiveSelections());

    fs::remove(path);

}

