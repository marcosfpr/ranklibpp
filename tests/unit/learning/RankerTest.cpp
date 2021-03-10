#include <memory>
#include <vector>
#include <iostream>
#include <filesystem>
#include <fstream>

#include <ranklib.hpp>
#include <gtest/gtest.h>

using std::cout;
using std::unique_ptr;
using std::shared_ptr;
using std::vector;

using namespace ranklib;

class MockRanker : public ranklib::Ranker{
    public:

        MockRanker(DataSet dataset, vector<int> features, unique_ptr<MetricScorer> scorer)
            : Ranker(dataset, move(scorer), features){}

        MockRanker(const MockRanker& rk): Ranker(rk) {}

        void start() override {}

        void learn() override {}

        double eval(ReadableDataPoint dp) override { return 0.0;}

        string toString() override { return "Mocked";}

        string model() override {return "Mocked";}

        void loadString(string model) override {}

        string name() override {return "Mocked";}

        void print() override {}
};

TEST(test_ranker, constructor) { 
    Sample sample = {
        std::make_shared<DataPoint>("0 qid:9 1:10 2:1.2 3:4.3 4:5.4 # doc1"),
        std::make_shared<DataPoint>("1 qid:9 1:11 2:2.2 3:4.5 4:5.6 # doc2"),
        std::make_shared<DataPoint>("0 qid:9 1:12 2:2.5 3:4.7 4:5.2 # doc3")
    };

    RankList rl(sample);

    DataSet dataset = {sample};

    vector<int> features = {1,2,3,4};

    unique_ptr<MetricScorer> scorer = std::make_unique<MAPScorer>();

    MockRanker ranker(dataset, features, scorer->clone());

    EXPECT_TRUE(&ranker != nullptr);
    EXPECT_TRUE(ranker.getFeatures() == features);

    MockRanker ranker2(ranker);

    EXPECT_TRUE(&ranker != &ranker2);
    EXPECT_TRUE(ranker2.getFeatures() == features);

    MockRanker ranker3(ranker2);

    vector<int> new_features = {1,3};
    ranker.setFeatures(new_features);

    ranker3 = ranker;

    EXPECT_TRUE(ranker3.getFeatures() == new_features);


}

TEST(test_ranker, operators) {
    Sample sample = {
        std::make_shared<DataPoint>("0 qid:9 1:10 2:1.2 3:4.3 4:5.4 # doc1"),
        std::make_shared<DataPoint>("1 qid:9 1:11 2:2.2 3:4.5 4:5.6 # doc2"),
        std::make_shared<DataPoint>("0 qid:9 1:12 2:2.5 3:4.7 4:5.2 # doc3")
    };

    RankList rl(sample);

    DataSet dataset = {sample};

    vector<int> features = {1,2,3,4};

    unique_ptr<MetricScorer> scorer = std::make_unique<MAPScorer>();

    MockRanker ranker(dataset, features, scorer->clone());


    ranker.setTrainingSet(dataset);
    ranker.setValidationSet(dataset);
    ranker.setScorer(scorer->clone());

    EXPECT_TRUE(ranker.getFeatures() == features);
    EXPECT_TRUE(ranker.getTrainingScore() == ranker.getValidationScore());
    EXPECT_TRUE(ranker.getTrainingScore() == 0.0);


}

TEST(test_ranker, save) {
    Sample sample = {
        std::make_shared<DataPoint>("0 qid:9 1:10 2:1.2 3:4.3 4:5.4 # doc1"),
        std::make_shared<DataPoint>("1 qid:9 1:11 2:2.2 3:4.5 4:5.6 # doc2"),
        std::make_shared<DataPoint>("0 qid:9 1:12 2:2.5 3:4.7 4:5.2 # doc3")
    };

    RankList rl(sample);

    DataSet dataset = {sample};

    vector<int> features = {1,2,3,4};

    unique_ptr<MetricScorer> scorer = std::make_unique<MAPScorer>();

    MockRanker ranker(dataset, features, scorer->clone());

    string file_path = "./mocked.txt";
    ranker.save(file_path);

    std::filesystem::path path = std::filesystem::path(file_path.c_str());

    ASSERT_TRUE(std::filesystem::exists(path));

    std::ifstream file_stream{file_path.c_str()};
    
    ASSERT_TRUE(!file_stream.fail());

    string response;
    string expected = "Generic Ranker Model";

    std::getline(file_stream, response);
    ASSERT_STREQ(response.c_str(), expected.c_str());

    std::filesystem::remove(path);

}
