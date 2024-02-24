CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
SRC_TESTS = s21_test.c $(wildcard tests/*.c)
SRC_FILES=$(wildcard s21_arithmetic/*.c) $(wildcard s21_comparison/*.c) $(wildcard s21_convertors/*.c) $(wildcard helpers/*.c) $(wildcard s21_another/*.c)

GCOVFLAGS = -L. --coverage
TEST_FLAGS = -lcheck

ifeq ($(shell uname), Linux)
	TEST_FLAGS += -lpthread -lrt -lsubunit -lm
endif


all: clean check-style s21_decimal.a test gcov_report

s21_decimal.a:
	$(CC) $(FLAGS) $(SRC_FILES) -c
	ar r s21_decimal.a *.o
	rm *.o

test: s21_decimal.a
	$(CC) $(FLAGS) -g $(SRC_TESTS) s21_decimal.a $(TEST_FLAGS) -o test

check-style:
	clang-format -n -style=Google *.h tests/*.h $(SRC_TESTS) $(SRC_FILES)
	
set-style:
	clang-format -i -style=Google *.h tests/*.h $(SRC_TESTS) $(SRC_FILES)

gcov_report: s21_decimal.a test
	$(CC) $(FLAGS) -w $(SRC_TESTS) $(SRC_FILES) s21_decimal.a $(TEST_FLAGS) $(GCOVFLAGS) -o test
	./test
	lcov -t s21_test -o test.info -c -d .
	genhtml -o test_html test.info
	open ./test_html/index.html

clean:
	rm -rf *.o *.a *.gch *.gcno *.gcna *.gcda *.info *.out test test_html test.dSYM report_make tests/*.o

check:
	clang-format -n *.c *.h s21_another/*.c s21_another/*.h s21_arithmetic/*.c s21_arithmetic/*.h  s21_comparison/*.c s21_comparison/*.h s21_convertors/*.c s21_convertors/*.h tests/*.c tests/*.h helpers/*.c helpers/*.h

clang:
	clang-format -i *.c *.h s21_another/*.c s21_another/*.h s21_arithmetic/*.c s21_arithmetic/*.h  s21_comparison/*.c s21_comparison/*.h s21_convertors/*.c s21_convertors/*.h tests/*.c tests/*.h helpers/*.c helpers/*.h

