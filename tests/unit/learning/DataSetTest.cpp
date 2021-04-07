#include <ltr.hpp>

#include <cstdlib>
#include <gtest/gtest.h>

using namespace ltr;

TEST(test_dataset, parsing) {
    string base_path = std::getenv("OHSUMED");
    DataSet training_samples = load_svmlight(base_path + "/Data/All/OHSUMED.txt");

    ASSERT_EQ(training_samples.size(), 106); // there are 106 queries on OHSUMED dataset
}