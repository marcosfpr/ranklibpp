#include <ltr.hpp>

#include <gtest/gtest.h>

using namespace ltr;

TEST(test_datapoints, constructor) {
    DataPoint* dp = new DataPoint();
    EXPECT_TRUE(dp != nullptr);

    //copying
    DataPoint dp2(*dp);
    EXPECT_TRUE(dp != &dp2);

    //moving
    DataPoint dp3 = std::move(dp2);
    EXPECT_TRUE(&dp3 != nullptr);

    delete dp;
}


TEST(test_datapoints, operators) {

    DataPoint dp;
    dp.setDescription("d1");

    ASSERT_STREQ(dp.getDescription().c_str(), "d1");

    DataPoint dp2;
    dp2 = dp;

    ASSERT_STREQ(dp2.getDescription().c_str(), "d1");
    EXPECT_TRUE(&dp != nullptr);

    DataPoint dp3;
    dp3 = std::move(dp);

    ASSERT_STREQ(dp3.getDescription().c_str(), "d1");
}

TEST(test_datapoints, getters_and_setters) {
    DataPoint dp;
    std::vector<float> features = {0, 21, 2.3, 4.5};

    dp.setCached(1.2);
    dp.setDescription("desc");
    dp.setFeatureVector(features);
    dp.setFeatureValue(1, 21);
    dp.setID("qid:10");
    dp.setLabel(1);
    std::string str = dp.toString();

    EXPECT_TRUE(dp.getCached() == 1.2);
    EXPECT_TRUE(dp.getDescription() == "desc");
    EXPECT_TRUE(dp.getFeatureValue(1) == 21);
    EXPECT_TRUE(dp.getFeatureVector() == features);
    EXPECT_TRUE(dp.getID() == "qid:10");
    EXPECT_TRUE(dp.getLabel() == 1);
    ASSERT_STREQ(dp.toString().c_str(),"1 qid:10 1:21.00 2:2.30 3:4.50 # desc");

    dp.resetCached();
    EXPECT_TRUE(dp.getCached() != 1.2);
    EXPECT_TRUE(dp.getFeatureCount() == 3);

}

TEST(test_datapoints, parse) {
    DataPoint dp("0 qid:9 1:10 # doc1");
    
    EXPECT_TRUE(dp.getLabel() == 0);
    EXPECT_TRUE(dp.getFeatureValue(1) == 10);
    EXPECT_TRUE(dp.getID() == "qid:9");
    ASSERT_STREQ(dp.getDescription().c_str(), "doc1");

    ASSERT_ANY_THROW(new DataPoint("-1 qid:9 1:10 # doc1"));

    
}

TEST(test_datapoints, limits){
    DataPoint dp("0 qid:9 1:10");
    ASSERT_ANY_THROW(dp.getFeatureValue(100));
    ASSERT_ANY_THROW(dp.setFeatureValue(0, 20));
}
