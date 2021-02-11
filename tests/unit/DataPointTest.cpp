#include <ranklib.hpp>

#include <check.h>

START_TEST(test_construct_datapoints) {
    DataPoint* dp = new DataPoint();
    ck_assert_ptr_ne(dp, nullptr);

    //copying
    DataPoint dp2(*dp);
    ck_assert_ptr_ne(dp, &dp2);

    //moving
    DataPoint dp3 = std::move(dp2);
    ck_assert_ptr_ne(&dp3, nullptr);

    delete dp;
}
END_TEST


Suite* make_sample_creation_suite(){
    Suite *s;
    TCase *tc_core;

    s = suite_create("Sample Creation Test Suite");

    /* Creation test case */
    tc_core = tcase_create("Test Cases of DataPoints");

    tcase_add_test(tc_core, test_construct_datapoints);

    suite_add_tcase(s, tc_core);

    return s;
}

Suite * make_sample_limits_suite() {
    Suite *s;
    TCase *tc_limits;

    s = suite_create("DataPoint Limits Test Suite");

    /* Limits test case */
    tc_limits = tcase_create("Simple Test Cases");

    // tcase_add_test(tc_limits, test_sample_create_neg);
    // tcase_add_test(tc_limits, test_sample_create_pos);

    // suite_add_tcase(s, tc_limits);

    return s;
}

int main(void) {
  int number_failed;
  SRunner *sr;

  sr = srunner_create(make_sample_creation_suite());
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_add_suite (sr, make_sample_limits_suite());
  srunner_set_log (sr, "test.log");
  srunner_set_xml (sr, "test.xml");
  srunner_run_all(sr, CK_VERBOSE);

  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}