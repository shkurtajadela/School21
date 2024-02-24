#include "s21_another.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int is_error = 0;  // должен быть запуск функции обработки ошибок
  if (isNan(&value)) {
    is_error = 1;
    makeNan(result);
  } else if (result == NULL) {
    is_error = 1;
  }

  if (!is_error) {
    memset(result, 0, sizeof(s21_decimal));
    int f = isInf(&value);
    if (f) {
      makeInf(result);
      setSign(result, f);
    } else {
      is_error = s21_truncate(value, result);

      if (getSign(value) == -1 && !s21_is_equal(value, *result)) {
        s21_decimal m_one = {{0, 0, 0, 0}};
        s21_from_int_to_decimal(-1, &m_one);
        s21_add(*result, m_one, result);
      }
    }
  }

  return is_error;
}
