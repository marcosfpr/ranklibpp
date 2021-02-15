#include <memory>
#include <vector>

#include <ranklib.hpp>
#include <gtest/gtest.h>

using std::shared_ptr;
using std::vector;

TEST(test_ranklists, constructor) { 
   
    sample_t sample = {
        std::make_shared<DataPoint>(DataPoint("0 qid:9 1:10 2:1.2 3:4.3 4:5.4 # doc1")),
        std::make_shared<DataPoint>(DataPoint("1 qid:9 1:11 2:2.2 3:4.5 4:5.6 # doc2")),
        std::make_shared<DataPoint>(DataPoint("0 qid:9 1:12 2:2.5 3:4.7 4:5.2 # doc3"))
    };

    RankList rl(sample);

    EXPECT_TRUE(&rl != nullptr);
    EXPECT_TRUE(rl.size() == 3);

    RankList rl2(rl);
    EXPECT_TRUE(rl2.size() == 3);

    vector<int> slice = {1, 2};
    RankList rl3(rl, slice, 0);
    EXPECT_TRUE(rl3.size() == 3); // size still 3
    EXPECT_TRUE(rl3.get(0)->getLabel() == 1); // but only uses 2 samples
    EXPECT_TRUE(rl3.get(1)->getLabel() == 0);

    RankList rl4 = std::move(rl);
    EXPECT_TRUE(rl4.size() == 3);
    EXPECT_TRUE(rl4.get(0)->getLabel() == 0);

}


TEST(test_ranklists, operators) {
    sample_t sample = {
        std::make_shared<DataPoint>(DataPoint("0 qid:9 1:10 2:1.2 3:4.3 4:5.4 # doc1")),
        std::make_shared<DataPoint>(DataPoint("1 qid:9 1:11 2:2.2 3:4.5 4:5.6 # doc2")),
        std::make_shared<DataPoint>(DataPoint("0 qid:9 1:12 2:2.5 3:4.7 4:5.2 # doc3"))
    };

    RankList rl(sample);

    EXPECT_TRUE(rl.size() == 3);

    RankList rl2 = rl; // copy

    EXPECT_TRUE(rl2.size() == 3);
    EXPECT_TRUE(&(*rl2.get(0)) != &(*rl.get(0))); //different portions of memory

    RankList rl3 = std::move(rl); // mode
    EXPECT_TRUE(rl3.size() == 3);
    // rl impl is null now
}

TEST(test_ranklists, utils) {
    sample_t sample = {
        std::make_shared<DataPoint>(DataPoint("0 qid:9 1:10 2:1.2 3:4.3 4:5.4 # doc1")),
        std::make_shared<DataPoint>(DataPoint("1 qid:9 1:11 2:2.2 3:4.5 4:5.6 # doc2")),
        std::make_shared<DataPoint>(DataPoint("0 qid:9 1:12 2:2.5 3:4.7 4:5.2 # doc3"))
    };

    RankList rl(sample);

    ASSERT_STREQ(rl.toString().c_str(), "<RankList object with 3 samples>");

    rl.set(2,std::make_shared<DataPoint>(DataPoint("0 qid:10 1:12 2:2.5 3:4.7 4:5.2 # doc1")));

    ASSERT_STREQ(rl.get(2)->getID().c_str(), "qid:10");

    ASSERT_ANY_THROW(rl.set(10, std::make_shared<DataPoint>(DataPoint())));
}

TEST(test_ranklists, ranking) {
    sample_t sample = {
        std::make_shared<DataPoint>(DataPoint("0 qid:9 1:10 2:1.2 3:4.3 4:5.4 # doc1")),
        std::make_shared<DataPoint>(DataPoint("1 qid:9 1:11 2:2.2 3:4.5 4:5.6 # doc2")),
        std::make_shared<DataPoint>(DataPoint("0 qid:9 1:12 2:2.5 3:4.7 4:5.2 # doc3"))
    };

    RankList rl(sample);

    RankList rl2 = std::move(rl.getPartialRanking(1));
    EXPECT_TRUE(rl2.size() == 3);
    ASSERT_STREQ(rl2.get(0)->getDescription().c_str(), "# doc3");
    ASSERT_STREQ(rl2.get(1)->getDescription().c_str(), "# doc2");
    ASSERT_STREQ(rl2.get(2)->getDescription().c_str(), "# doc1");


    RankList rl3 = std::move(rl.getRanking());
    EXPECT_TRUE(rl3.size() == 3);
    ASSERT_STREQ(rl3.get(0)->getDescription().c_str(), "# doc2");
    ASSERT_STREQ(rl3.get(1)->getDescription().c_str(), "# doc1");
    ASSERT_STREQ(rl3.get(2)->getDescription().c_str(), "# doc3");
}

