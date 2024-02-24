#include <check.h>

#include "ddd_viewer.h"

static void load_array(int len, double from[], double to[]) {
  for (int j = 0; j < len; j++) to[j] = from[j];
}

START_TEST(test_1) {
  FILE *file = fopen("./models/cube.obj", "r");
  ck_assert_ptr_nonnull(file);
  if (file) fclose(file);
}
END_TEST

START_TEST(test_2) {
  char uri[] = "./models/cube.obj";
  data_t *obj = calloc(1, sizeof(data_t));
  ck_assert_int_eq(parse_obj_file(uri, obj), 1);
  ck_assert_int_eq(allocate_memory_for_array_of_vertexes(uri, obj), 1);
  obj->numbers_of_vertexes_in_facets = 0;
  ck_assert_int_eq(allocate_memory_for_array_vertexes_in_facets(uri, obj), 1);
  ck_assert_int_eq(allocate_memory_for_array_of_facets(uri, obj), 1);
  ck_assert_uint_eq(obj->count_of_vertexes, 8);
  ck_assert_uint_eq(obj->count_of_edges, 6);
  ck_assert_uint_eq(obj->numbers_of_vertexes_in_facets, 48);
  obj->count_of_vertexes = 8;
  double array_before_move[] = {-1.0, -1.0, -1.0, -1.0, -1.0, 1.0,  -1.0, 1.0,
                                -1.0, -1.0, 1.0,  1.0,  1.0,  -1.0, -1.0, 1.0,
                                -1.0, 1.0,  1.0,  1.0,  -1.0, 1.0,  1.0,  1.0};
  double array_after_move[] = {9.0,  14.0, -6.0, 9.0,  14.0, -4.0, 9.0,  16.0,
                               -6.0, 9.0,  16.0, -4.0, 11.0, 14.0, -6.0, 11.0,
                               14.0, -4.0, 11.0, 16.0, -6.0, 11.0, 16.0, -4.0};
  load_array(24, array_before_move, obj->single_array_for_vertexes);
  move_object(obj, 10.0, 15.0, -5.0);
  for (int j = 0; j < 24; j++) {
    ck_assert_double_eq_tol(obj->single_array_for_vertexes[j],
                            array_after_move[j], 0.1);
  }
  double array_after_scale[] = {4.5,  7.0,  -3.0, 4.5,  7.0,  -2.0, 4.5,  8.0,
                                -3.0, 4.5,  8.0,  -2.0, 5.5,  7.0,  -3.0, 5.5,
                                7.0,  -2.0, 5.5,  8.0,  -3.0, 5.5,  8.0,  -2.0};
  scale_object(obj, 0.5);
  for (int j = 0; j < 24; j++) {
    ck_assert_double_eq_tol(obj->single_array_for_vertexes[j],
                            array_after_scale[j], 0.1);
  }
  rotate_object(obj, 360, -360, 360);
  for (int j = 0; j < 24; j++) {
    ck_assert_double_eq_tol(obj->single_array_for_vertexes[j],
                            array_after_scale[j], 0.1);
  }
  free_struct(obj);
}
END_TEST

int main(void) {
  Suite *suite_ = suite_create("_suite");
  TCase *tcase_ = tcase_create("_case");

  tcase_add_test(tcase_, test_1);
  tcase_add_test(tcase_, test_2);

  suite_add_tcase(suite_, tcase_);
  SRunner *runner_ = srunner_create(suite_);
  srunner_run_all(runner_, CK_ENV);
  int failed_count = srunner_ntests_failed(runner_);
  srunner_free(runner_);
  return (failed_count == 0) ? 0 : 1;
}