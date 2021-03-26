#include <string>
#include <list>

#include <ltr.hpp>
#include <gtest/gtest.h>

using std::list;
using std::string;

using namespace ltr;

TEST(test_key_value, parse)
{

    string raw = "1:0.2 2:0.4 3:0.5";

    list<KeyValue> pairs = ltr::parseKeyValue(raw);

    EXPECT_TRUE(pairs.size() == 3);

    auto it = pairs.begin();

    ASSERT_STREQ((*it).value.c_str(), "0.2");

    ++it;

    ASSERT_STREQ((*it).value.c_str(), "0.4");

    ++it;

    ASSERT_STREQ((*it).value.c_str(), "0.5");

}
