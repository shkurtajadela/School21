#include "s21_test_main.h"

/*
double bank_round(double number)
*/
TEST(CommonSuite, BankRound) {
  EXPECT_NEAR(s21::bankRound(126.5), 126.0, EPS);
  EXPECT_NEAR(s21::bankRound(129.5), 130.0, EPS);
  EXPECT_NEAR(s21::bankRound(-123.5), -124.0, EPS);
  EXPECT_NEAR(s21::bankRound(-124.5), -124.0, EPS);
  EXPECT_NEAR(s21::bankRound(124.6), 125.0, EPS);
  EXPECT_NEAR(s21::bankRound(-124.6), -125.0, EPS);
}

TEST(CommonSuite, bankRoundTwoDecimal) {
  EXPECT_NEAR(s21::bankRoundTwoDecimal(1.265), 1.26, EPS);
  EXPECT_NEAR(s21::bankRoundTwoDecimal(1.295), 1.3, EPS);
  EXPECT_NEAR(s21::bankRoundTwoDecimal(-1.235), -1.24, EPS);
  EXPECT_NEAR(s21::bankRoundTwoDecimal(-1.245), -1.24, EPS);
  EXPECT_NEAR(s21::bankRoundTwoDecimal(1.246), 1.25, EPS);
  EXPECT_NEAR(s21::bankRoundTwoDecimal(-1.246), -1.25, EPS);
}

TEST(CommonSuite, BankRoundLong) {
  EXPECT_NEAR(s21::bankRoundLong(126.5L), 126.0L, EPS);
  EXPECT_NEAR(s21::bankRoundLong(129.5L), 130.0L, EPS);
  EXPECT_NEAR(s21::bankRoundLong(-123.5L), -124.0L, EPS);
  EXPECT_NEAR(s21::bankRoundLong(-124.5L), -124.0L, EPS);
  EXPECT_NEAR(s21::bankRoundLong(124.6L), 125.0L, EPS);
  EXPECT_NEAR(s21::bankRoundLong(-124.6L), -125.0L, EPS);
}

TEST(CommonSuite, bankRoundLongTwoDecimal) {
  EXPECT_NEAR(s21::bankRoundLongTwoDecimal(1.265L), 1.26L, EPS);
  EXPECT_NEAR(s21::bankRoundLongTwoDecimal(1.295L), 1.3L, EPS);
  EXPECT_NEAR(s21::bankRoundLongTwoDecimal(-1.235L), -1.24L, EPS);
  EXPECT_NEAR(s21::bankRoundLongTwoDecimal(-1.245L), -1.24L, EPS);
  EXPECT_NEAR(s21::bankRoundLongTwoDecimal(1.246L), 1.25L, EPS);
  EXPECT_NEAR(s21::bankRoundLongTwoDecimal(-1.246L), -1.25L, EPS);
}

TEST(CommonSuite, DateConstruct) {
  EXPECT_THROW(s21::Date date(31, 12, 1899), std::invalid_argument);
  EXPECT_THROW(s21::Date date(32, 12, 2012), std::invalid_argument);
  EXPECT_THROW(s21::Date date(0, 12, 2012), std::invalid_argument);
  EXPECT_THROW(s21::Date date(5, 0, 2012), std::invalid_argument);
  EXPECT_THROW(s21::Date date(5, 13, 2012), std::invalid_argument);
  EXPECT_THROW(s21::Date date(30, 2, 2012), std::invalid_argument);
  EXPECT_THROW(s21::Date date(29, 2, 2001), std::invalid_argument);
  EXPECT_THROW(s21::Date date(31, 11, 2020), std::invalid_argument);
  s21::Date date(31, 12, 2012);
  EXPECT_EQ(date.getDay(), 31);
  EXPECT_EQ(date.getMonth(), 12);
  EXPECT_EQ(date.getYear(), 2012);
}

TEST(CommonSuite, DateSetDate) {
  s21::Date date;
  time_t t = std::time(NULL);
  struct std::tm current = *std::localtime(&t);
  EXPECT_EQ(date.getDay(), current.tm_mday);
  EXPECT_EQ(date.getMonth(), current.tm_mon + 1);
  EXPECT_EQ(date.getYear(), current.tm_year + 1900);
  date.setDate(31, 12, 2012);
  EXPECT_EQ(date.getDay(), 31);
  EXPECT_EQ(date.getMonth(), 12);
  EXPECT_EQ(date.getYear(), 2012);
  date.setDate(1, 1, 1900);
  EXPECT_EQ(date.getDay(), 1);
  EXPECT_EQ(date.getMonth(), 1);
  EXPECT_EQ(date.getYear(), 1900);
  date.setDate(31, 12, 2700);
  EXPECT_EQ(date.getDay(), 31);
  EXPECT_EQ(date.getMonth(), 12);
  EXPECT_EQ(date.getYear(), 2700);
  date.setDate(29, 2, 2000);
  EXPECT_EQ(date.getDay(), 29);
  EXPECT_EQ(date.getMonth(), 2);
  EXPECT_EQ(date.getYear(), 2000);
  EXPECT_THROW(date.setDate(31, 12, 1899), std::invalid_argument);
  // EXPECT_THROW(date.setDate(1, 1, 2701), std::invalid_argument);
  EXPECT_THROW(date.setDate(32, 12, 2012), std::invalid_argument);
  EXPECT_THROW(date.setDate(0, 12, 2012), std::invalid_argument);
  EXPECT_THROW(date.setDate(5, 0, 2012), std::invalid_argument);
  EXPECT_THROW(date.setDate(5, 13, 2012), std::invalid_argument);
  EXPECT_THROW(date.setDate(30, 2, 2012), std::invalid_argument);
  EXPECT_THROW(date.setDate(29, 2, 2001), std::invalid_argument);
  EXPECT_THROW(date.setDate(31, 11, 2020), std::invalid_argument);
}

TEST(CommonSuite, DateSubtraction) {
  s21::Date date1(31, 12, 2012);
  s21::Date date2(31, 12, 2012);
  EXPECT_EQ(date2.subtract(date1), 0);
  date1.setDate(30, 12, 2012);
  date2.setDate(31, 12, 2012);
  EXPECT_EQ(date2.subtract(date1), 1);
  date1.setDate(31, 12, 2012);
  date2.setDate(30, 12, 2012);
  EXPECT_EQ(date2.subtract(date1), -1);
  date1.setDate(31, 12, 2012);
  date2.setDate(1, 1, 2013);
  EXPECT_EQ(date2.subtract(date1), 1);
  date1.setDate(1, 1, 2013);
  date2.setDate(31, 12, 2012);
  EXPECT_EQ(date2.subtract(date1), -1);
  date1.setDate(9, 3, 2012);
  date2.setDate(29, 2, 2024);
  EXPECT_EQ(date2.subtract(date1), 4374);
  date1.setDate(29, 2, 2024);
  date2.setDate(9, 3, 2012);
  EXPECT_EQ(date2.subtract(date1), -4374);
  date1.setDate(1, 1, 1900);
  date2.setDate(21, 5, 2700);
  EXPECT_EQ(date2.subtract(date1), 292334);
  date1.setDate(21, 5, 2700);
  date2.setDate(1, 1, 1900);
  EXPECT_EQ(date2.subtract(date1), -292334);
  date1.setDate(1, 1, 1900);
  date2.setDate(31, 12, 9999);
  EXPECT_EQ(date2.subtract(date1), 2958463);
  date1.setDate(31, 12, 9999);
  date2.setDate(1, 1, 1900);
  EXPECT_EQ(date2.subtract(date1), -2958463);

  date1.setDate(30, 12, 2012);
  date2.setDate(31, 12, 2012);
  EXPECT_EQ(date2 | date1, 1);
  date1.setDate(31, 12, 2012);
  date2.setDate(30, 12, 2012);
  EXPECT_EQ(date2 | date1, -1);
  date1.setDate(31, 12, 2012);
  date2.setDate(1, 1, 2013);
  EXPECT_EQ(date2 | date1, 1);
  date1.setDate(1, 1, 2013);
  date2.setDate(31, 12, 2012);
  EXPECT_EQ(date2 | date1, -1);
  date1.setDate(9, 3, 2012);
  date2.setDate(29, 2, 2024);
  EXPECT_EQ(date2 | date1, 4374);
  date1.setDate(29, 2, 2024);
  date2.setDate(9, 3, 2012);
  EXPECT_EQ(date2 | date1, -4374);
  date1.setDate(1, 1, 1900);
  date2.setDate(21, 5, 2700);
  EXPECT_EQ(date2 | date1, 292334);
  date1.setDate(21, 5, 2700);
  date2.setDate(1, 1, 1900);
  EXPECT_EQ(date2 | date1, -292334);
  date1.setDate(1, 1, 1900);
  date2.setDate(31, 12, 9999);
  EXPECT_EQ(date2 | date1, 2958463);
  date1.setDate(31, 12, 9999);
  date2.setDate(1, 1, 1900);
  EXPECT_EQ(date2 | date1, -2958463);
}

TEST(CommonSuite, DateComparison) {
  s21::Date date1(31, 12, 2012);
  s21::Date date2(31, 12, 2012);
  EXPECT_TRUE(date1 == date2);
  EXPECT_FALSE(date1 != date2);
  EXPECT_TRUE(date1 >= date2);
  EXPECT_TRUE(date1 <= date2);
  EXPECT_FALSE(date1 > date2);
  EXPECT_FALSE(date1 < date2);
  date1.setDate(30, 12, 2012);
  date2.setDate(31, 12, 2012);
  EXPECT_FALSE(date1 == date2);
  EXPECT_TRUE(date1 != date2);
  EXPECT_FALSE(date1 >= date2);
  EXPECT_TRUE(date1 <= date2);
  EXPECT_FALSE(date1 > date2);
  EXPECT_TRUE(date1 < date2);
  date1.setDate(31, 12, 2012);
  date2.setDate(30, 12, 2012);
  EXPECT_FALSE(date1 == date2);
  EXPECT_TRUE(date1 != date2);
  EXPECT_TRUE(date1 >= date2);
  EXPECT_FALSE(date1 <= date2);
  EXPECT_TRUE(date1 > date2);
  EXPECT_FALSE(date1 < date2);
  date1.setDate(31, 12, 2012);
  date2.setDate(1, 1, 2013);
  EXPECT_FALSE(date1 == date2);
  EXPECT_TRUE(date1 != date2);
  EXPECT_FALSE(date1 >= date2);
  EXPECT_TRUE(date1 <= date2);
  EXPECT_FALSE(date1 > date2);
  EXPECT_TRUE(date1 < date2);
  date1.setDate(1, 1, 2013);
  date2.setDate(31, 12, 2012);
  EXPECT_FALSE(date1 == date2);
  EXPECT_TRUE(date1 != date2);
  EXPECT_TRUE(date1 >= date2);
  EXPECT_FALSE(date1 <= date2);
  EXPECT_TRUE(date1 > date2);
  EXPECT_FALSE(date1 < date2);
  date1.setDate(9, 3, 2012);
  date2.setDate(29, 2, 2024);
  EXPECT_FALSE(date1 == date2);
  EXPECT_TRUE(date1 != date2);
  EXPECT_FALSE(date1 >= date2);
  EXPECT_TRUE(date1 <= date2);
  EXPECT_FALSE(date1 > date2);
  EXPECT_TRUE(date1 < date2);
  date1.setDate(29, 2, 2024);
  date2.setDate(9, 3, 2012);
  EXPECT_FALSE(date1 == date2);
  EXPECT_TRUE(date1 != date2);
  EXPECT_TRUE(date1 >= date2);
  EXPECT_FALSE(date1 <= date2);
  EXPECT_TRUE(date1 > date2);
  EXPECT_FALSE(date1 < date2);
  date1.setDate(1, 1, 1900);
  date2.setDate(31, 12, 9999);
  EXPECT_FALSE(date1 == date2);
  EXPECT_TRUE(date1 != date2);
  EXPECT_FALSE(date1 >= date2);
  EXPECT_TRUE(date1 <= date2);
  EXPECT_FALSE(date1 > date2);
  EXPECT_TRUE(date1 < date2);
  date1.setDate(31, 12, 9999);
  date2.setDate(1, 1, 1900);
  EXPECT_FALSE(date1 == date2);
  EXPECT_TRUE(date1 != date2);
  EXPECT_TRUE(date1 >= date2);
  EXPECT_FALSE(date1 <= date2);
  EXPECT_TRUE(date1 > date2);
  EXPECT_FALSE(date1 < date2);
}

TEST(CommonSuite, DateOperators) {
  s21::Date date1(31, 12, 2012);
  s21::Date date2(31, 12, 2012);
  date1 = date2 - 0;
  date2 = date1 + 0;
  EXPECT_TRUE(date2 == date1);
  date1.setDate(30, 12, 2012);
  date2.setDate(31, 12, 2012);
  date2--;
  EXPECT_TRUE(date2 == date1);
  date1.setDate(31, 12, 2012);
  date2.setDate(30, 12, 2012);
  date2++;
  EXPECT_TRUE(date2 == date1);
  date1.setDate(28, 2, 2014);
  date2.setDate(1, 3, 2014);
  --date2;
  EXPECT_TRUE(date2 == date1);
  date1.setDate(1, 3, 2014);
  date2.setDate(28, 2, 2014);
  ++date2;
  EXPECT_TRUE(date2 == date1);
  date1.setDate(31, 12, 2012);
  date2.setDate(1, 1, 2013);
  date2 -= 1;
  EXPECT_TRUE(date2 == date1);
  date1.setDate(1, 1, 2013);
  date2.setDate(31, 12, 2012);
  date2 = date2 + 1;
  EXPECT_TRUE(date2 == date1);
  date1.setDate(9, 3, 2012);
  date2.setDate(29, 2, 2024);
  date2 -= 4374;
  EXPECT_TRUE(date2 == date1);
  date1.setDate(29, 2, 2024);
  date2.setDate(9, 3, 2012);
  date1 += -4374;
  EXPECT_TRUE(date2 == date1);
  date1.setDate(1, 1, 1900);
  date2.setDate(21, 5, 2700);
  date2.addDays(-292334);
  EXPECT_TRUE(date2 == date1);
  date1.setDate(21, 5, 2700);
  date2.setDate(1, 1, 1900);
  date2 -= -292334;
  EXPECT_TRUE(date2 == date1);
  date1.setDate(1, 1, 1900);
  date2.setDate(31, 12, 9999);
  date1.addDays(2958463);
  EXPECT_TRUE(date2 == date1);
  date1.setDate(31, 12, 9999);
  date2.setDate(1, 1, 1900);
  date2 = 2958463 + date2;
  EXPECT_TRUE(date2 == date1);
}

TEST(CommonSuite, AddMonths) {
  s21::Date date1(31, 12, 2012);
  s21::Date date2(31, 12, 2012);
  date1.addMonths(0);
  EXPECT_TRUE(date2 == date1);
  date1.setDate(31, 12, 2012);
  date2.setDate(31, 12, 2013);
  date1.addMonths(12);
  EXPECT_TRUE(date2 == date1);
  date1.setDate(31, 12, 2012);
  date2.setDate(31, 8, 2012);
  date1.addMonths(-4);
  EXPECT_TRUE(date2 == date1);
  date1.setDate(31, 12, 2012);
  date2.setDate(30, 11, 2011);
  date1.addMonths(-13);
  EXPECT_TRUE(date2 == date1);
  date1.setDate(31, 12, 2012);
  date2.setDate(30, 6, 2010);
  date1.addMonths(-30);
  EXPECT_TRUE(date2 == date1);
  date1.setDate(28, 2, 2014);
  date2.setDate(28, 4, 2014);
  date1.addMonths(2);
  EXPECT_TRUE(date2 == date1);
  date1.setDate(29, 1, 2014);
  date2.setDate(28, 2, 2014);
  date1.addMonths(1);
  EXPECT_TRUE(date2 == date1);
  date1.setDate(31, 1, 2014);
  date2.setDate(29, 2, 2016);
  date1.addMonths(25);
  EXPECT_TRUE(date2 == date1);
}

TEST(CommonSuite, AddYears) {
  s21::Date date1(31, 12, 2012);
  s21::Date date2(31, 12, 2012);
  date1.addYears(0);
  EXPECT_TRUE(date2 == date1);
  date1.setDate(31, 12, 2012);
  date2.setDate(31, 12, 2024);
  date1.addYears(12);
  EXPECT_TRUE(date2 == date1);
  date1.setDate(31, 12, 2012);
  date2.setDate(31, 12, 1999);
  date1.addYears(-13);
  EXPECT_TRUE(date2 == date1);
  date1.setDate(28, 2, 2014);
  date2.setDate(28, 2, 2016);
  date1.addYears(2);
  EXPECT_TRUE(date2 == date1);
  date1.setDate(29, 2, 2016);
  date2.setDate(28, 2, 2019);
  date1.addYears(3);
  EXPECT_TRUE(date2 == date1);
}

TEST(CommonSuite, ShiftMonths) {
  s21::Date date1(31, 12, 2012);
  s21::Date date2(31, 12, 2012);
  date1 = date1.shiftMonths(0);
  EXPECT_TRUE(date2 == date1);
  date1.setDate(31, 12, 2012);
  date2.setDate(31, 12, 2013);
  date1 = date1.shiftMonths(12);
  EXPECT_TRUE(date2 == date1);
  date1.setDate(31, 12, 2012);
  date2.setDate(31, 8, 2012);
  date1 = date1.shiftMonths(-4);
  EXPECT_TRUE(date2 == date1);
  date1.setDate(31, 12, 2012);
  date2.setDate(30, 11, 2011);
  date1 = date1.shiftMonths(-13);
  EXPECT_TRUE(date2 == date1);
  date1.setDate(31, 12, 2012);
  date2.setDate(30, 6, 2010);
  date1 = date1.shiftMonths(-30);
  EXPECT_TRUE(date2 == date1);
  date1.setDate(28, 2, 2014);
  date2.setDate(28, 4, 2014);
  date1 = date1.shiftMonths(2);
  EXPECT_TRUE(date2 == date1);
  date1.setDate(29, 1, 2014);
  date2.setDate(28, 2, 2014);
  date1 = date1.shiftMonths(1);
  EXPECT_TRUE(date2 == date1);
  date1.setDate(31, 1, 2014);
  date2.setDate(29, 2, 2016);
  date1 = date1.shiftMonths(25);
  EXPECT_TRUE(date2 == date1);
}
