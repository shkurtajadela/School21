GCC = g++ -std=c++17 -Wall -Wextra -Werror
LIBS = 
LINUX_LIBS = -lsubunit -lrt -lpthread -lm
DEBUG = -fsanitize=address
VALGRIND_FLAGS = --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose
GCOV_KEEP = --keep-going
GCOV_ERR = --ignore-errors inconsistent
OS = $(shell uname -s)

FULL_VAL_LEAK_CHECK = --leak-check=full --show-leak-kinds=all --track-origins=yes --tool=memcheck --show-reachable=yes

SRC_DIR = containers/
TEST_DIR = all_tests/
SRC = $(wildcard $(SRC_DIR)*.cpp)
TEST_SRC = $(wildcard $(TEST_DIR)*.cpp)
OBJ = $(SRC:.cpp=.o)

.PHONY: all test valgrind clang clean

ifeq ($(OS), Linux)
	LIBS += -lgmock -pthread
endif

ifeq ($(OS), Darwin)
    GTEST_CFLAGS = $(shell pkg-config --cflags gtest)
    GTEST_LIBS = $(shell pkg-config --libs gtest)
    LIBS += $(GTEST_LIBS)
    CFLAGS += $(GTEST_CFLAGS)
else
    LIBS += -lgtest -lgtest_main
endif

all: clean test

test: clean
	$(GCC) $(CFLAGS) $(SRC) $(TEST_SRC) -o test $(LIBS)
	./test --gtest_repeat=10 --gtest_break_on_failure

# Only for Linux
valgrind_linux: clean
	$(GCC) $(CFLAGS) $(SRC) $(TEST_SRC) -o test $(LIBS) $(LINUX_LIBS)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./test

valgrind: test
	valgrind $(FULL_VAL_LEAK_CHECK) ./test

clang:
	clang-format -n $(wildcard $(SRC_DIR)*.h) $(wildcard $(SRC_DIR)*.tpp)

clean:
	rm -rf a.out*
	rm -rf gtest.*o
	rm -rf test*
	rm -rf *.gcda
	rm -rf *.dSYM
	rm -rf *.gcno
	rm -rf main
