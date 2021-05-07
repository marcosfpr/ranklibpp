#include <memory>
#include <list>

#include <ltr.hpp>
#include <gtest/gtest.h>

using std::unique_ptr;
using std::shared_ptr;
using std::vector;

using namespace ltr;

TEST(test_precisionscorer, constructor) {

    auto* scorer = new PrecisionScorer(2);
    PrecisionScorer copy;
    copy = *scorer;

    PrecisionScorer copy2(copy);


    EXPECT_TRUE(scorer != nullptr);
    EXPECT_TRUE(&copy != scorer);
    EXPECT_TRUE(&copy != &copy2);

    EXPECT_TRUE(scorer->getDepth() == 2);
    scorer->setDepth(3);
    EXPECT_TRUE(scorer->getDepth() == 3);

    unique_ptr<MetricScorer> ptr_scorer(scorer);
    unique_ptr<MetricScorer> ptr2_scorer = ptr_scorer->clone();

    EXPECT_TRUE(ptr_scorer != ptr2_scorer);

}


TEST(test_precisionscorer, scores) {
    PrecisionScorer scorer(2);

    Sample sample1 = {
            std::make_shared<DataPoint>(DataPoint("0 qid:9 1:10 2:1.2 3:4.3 4:5.4 # doc1")),
            std::make_shared<DataPoint>(DataPoint("1 qid:9 1:11 2:2.2 3:4.5 4:5.6 # doc2")),
            std::make_shared<DataPoint>(DataPoint("0 qid:9 1:12 2:2.5 3:4.7 4:5.2 # doc3"))
    };

    RankList rl1(sample1);
    ASSERT_NEAR(scorer.score(rl1), 0.5, 0.001);


    Sample sample2 = {
            std::make_shared<DataPoint>(DataPoint("1 qid:9 1:10 2:1.2 3:4.3 4:5.4 # doc1")),
            std::make_shared<DataPoint>(DataPoint("0 qid:9 1:11 2:2.2 3:4.5 4:5.6 # doc2")),
            std::make_shared<DataPoint>(DataPoint("1 qid:9 1:12 2:2.5 3:4.7 4:5.2 # doc3"))
    };

    RankList rl2(sample2);
    ASSERT_NEAR(scorer.score(rl2), 0.5, 0.001);

    Sample sample3 = {
            std::make_shared<DataPoint>(DataPoint("0 qid:9 1:10 2:1.2 3:4.3 4:5.4 # doc1")),
            std::make_shared<DataPoint>(DataPoint("0 qid:9 1:11 2:2.2 3:4.5 4:5.6 # doc2")),
            std::make_shared<DataPoint>(DataPoint("0 qid:9 1:12 2:2.5 3:4.7 4:5.2 # doc3"))
    };

    RankList rl3(sample3);
    ASSERT_FLOAT_EQ(scorer.score(rl3), 0.0);


    DataSet l {rl1, rl2, rl3};
    ASSERT_NEAR(scorer.score(l), 0.3333, 0.001);

}
