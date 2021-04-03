#include <memory>
#include <vector>
#include <iostream>
#include <experimental/filesystem>
#include <fstream>

#include <ltr.hpp>
#include <gtest/gtest.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using std::cout;
using std::unique_ptr;
using std::shared_ptr;
using std::vector;
namespace fs = std::experimental::filesystem;
namespace pt = boost::property_tree;

using namespace ltr;

class MockRanker : public ltr::Ranker{
    public:

        MockRanker(DataSet dataset, vector<int> features, unique_ptr<MetricScorer> scorer)
            : Ranker(dataset, move(scorer), features){}
};

TEST(test_ranker, constructor) { 
    Sample sample = {
        std::make_shared<DataPoint>("0 qid:9 1:10 2:1.2 3:4.3 4:5.4 # doc1"),
        std::make_shared<DataPoint>("1 qid:9 1:11 2:2.2 3:4.5 4:5.6 # doc2"),
        std::make_shared<DataPoint>("0 qid:9 1:12 2:2.5 3:4.7 4:5.2 # doc3")
    };

    RankList rl(sample);

    DataSet dataset;
    dataset.push_back(std::move(rl));

    vector<int> features = {1,2,3,4};

    unique_ptr<MetricScorer> scorer = std::make_unique<MAPScorer>();

    MockRanker ranker(dataset, features, scorer->clone());

    EXPECT_TRUE(ranker.getFeatures() == features);
}

TEST(test_ranker, operators) {
    Sample sample = {
        std::make_shared<DataPoint>("0 qid:9 1:10 2:1.2 3:4.3 4:5.4 # doc1"),
        std::make_shared<DataPoint>("1 qid:9 1:11 2:2.2 3:4.5 4:5.6 # doc2"),
        std::make_shared<DataPoint>("0 qid:9 1:12 2:2.5 3:4.7 4:5.2 # doc3")
    };

    RankList rl(sample);

    DataSet dataset;
    dataset.push_back(std::move(rl));

    vector<int> features = {1,2,3,4};

    unique_ptr<MetricScorer> scorer = std::make_unique<MAPScorer>();

    MockRanker ranker(dataset, {}, scorer->clone());


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

    DataSet dataset;
    dataset.push_back(std::move(rl));

    vector<int> features = {1,2,3,4};

    unique_ptr<MetricScorer> scorer = std::make_unique<MAPScorer>();

    MockRanker ranker(dataset, features, scorer->clone());

    string file_path = "./mocked.json";
    ranker.save(file_path);

    fs::path path = fs::path(file_path.c_str());

    ASSERT_TRUE(fs::exists(path));

    string expected = "Ranker";
    pt::ptree root;
    pt::read_json(file_path, root);

    ASSERT_STREQ(root.get<string>("model").c_str(), expected.c_str());

    ranker.load(file_path);
    ASSERT_EQ(ranker.getParameters().size(), 0);

    fs::remove(path);

}

TEST(test_ranker, virtuals) {
    Sample sample = {
        std::make_shared<DataPoint>("0 qid:9 1:10 2:1.2 3:4.3 4:5.4 # doc1"),
        std::make_shared<DataPoint>("1 qid:9 1:11 2:2.2 3:4.5 4:5.6 # doc2"),
        std::make_shared<DataPoint>("0 qid:9 1:12 2:2.5 3:4.7 4:5.2 # doc3")
    };

    RankList rl(sample);

    DataSet dataset;
    dataset.push_back(rl);

    vector<int> features = {1,2,3,4};

    unique_ptr<MetricScorer> scorer = std::make_unique<MAPScorer>();

    MockRanker ranker(dataset, features, scorer->clone());

    ASSERT_ANY_THROW(ranker.fit());
    ASSERT_ANY_THROW(ranker.predict(rl.get(1)));
}
