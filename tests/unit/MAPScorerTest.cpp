#include <memory>
#include <list>

#include <ranklib.hpp>
#include <gtest/gtest.h>

using std::shared_ptr;
using std::vector;

using namespace ranklib;

TEST(test_mapscorer, constructor) { 
   
   MAPScorer* scorer = new MAPScorer();
   MAPScorer copy;
   copy = *scorer;

   MAPScorer copy2(copy);


   EXPECT_TRUE(scorer != nullptr);
   EXPECT_TRUE(&copy != scorer);
   EXPECT_TRUE(&copy != &copy2);

   EXPECT_TRUE(scorer->getDepth() == 0);
   scorer->setDepth(1);
   EXPECT_TRUE(scorer->getDepth() == 1);

}


TEST(test_mapscorer, scores) { 
   MAPScorer scorer;

   sample_t sample1 = {
        std::make_shared<DataPoint>(DataPoint("0 qid:9 1:10 2:1.2 3:4.3 4:5.4 # doc1")),
        std::make_shared<DataPoint>(DataPoint("1 qid:9 1:11 2:2.2 3:4.5 4:5.6 # doc2")),
        std::make_shared<DataPoint>(DataPoint("0 qid:9 1:12 2:2.5 3:4.7 4:5.2 # doc3"))
    };

   RankList rl1(sample1);
   ASSERT_NEAR(scorer.score(rl1), 0.5, 0.001);


   sample_t sample2 = {
        std::make_shared<DataPoint>(DataPoint("1 qid:9 1:10 2:1.2 3:4.3 4:5.4 # doc1")),
        std::make_shared<DataPoint>(DataPoint("0 qid:9 1:11 2:2.2 3:4.5 4:5.6 # doc2")),
        std::make_shared<DataPoint>(DataPoint("1 qid:9 1:12 2:2.5 3:4.7 4:5.2 # doc3"))
    };

   RankList rl2(sample2);
   ASSERT_NEAR(scorer.score(rl2), 0.8333, 0.001);


   sample_t sample3 = {
        std::make_shared<DataPoint>(DataPoint("0 qid:9 1:10 2:1.2 3:4.3 4:5.4 # doc1")),
        std::make_shared<DataPoint>(DataPoint("0 qid:9 1:11 2:2.2 3:4.5 4:5.6 # doc2")),
        std::make_shared<DataPoint>(DataPoint("0 qid:9 1:12 2:2.5 3:4.7 4:5.2 # doc3"))
    };

   RankList rl3(sample3);
   ASSERT_FLOAT_EQ(scorer.score(rl3), 0.0);


   std::list<RankList> l = {sample1, sample2, sample3};   
   ASSERT_NEAR(scorer.score(std::move(l)), 0.4444, 0.001);


}