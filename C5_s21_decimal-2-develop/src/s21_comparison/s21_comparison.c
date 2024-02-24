#include "s21_comparison.h"

// start comparation helpers
////
int isInf(const s21_decimal *el) {
  int res = 0;
  if (el != NULL) {
    if (getPower(*el) == 255 && (el->bits[2] == 0) && (el->bits[1] == 0) &&
        (el->bits[0] == 0)) {
      res = 1;
    }

    if (getSign(*el) == -1) {
      res = -res;
    }
  }

  return res;
}

int isNan(const s21_decimal *el) {
  int res = 0;
  if (el != NULL) {
    if (getPower(*el) == 255 && (el->bits[2] == 2147483648) &&
        (el->bits[1] == 0) && (el->bits[0] == 0)) {
      res = 1;
    }
  }
  return res;
}
