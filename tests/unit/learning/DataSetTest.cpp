#include <ltr.hpp>

#include <cstdlib>
#include <gtest/gtest.h>

using namespace ltr;

TEST(test_dataset, parsing) {
    DataSet training_samples = load_svmlight(std::getenv("MOVIES_BENCHMARK_TRAIN"));

    ASSERT_EQ(training_samples.size(), 80);
}