MAKE = make
CC = gcc
CFLAGS =-Wall -Werror -Wextra -Wpedantic -g -std=c++17
UI_SRC = $(wildcard ./view/*.cpp, ./view/*.h)
CONTROLLER_SRC = $(wildcard ./controller/*.cpp, ./controller/*.h)
MODEL_SRC = $(wildcard ./model/*.cpp)
MODEL_H = $(wildcard ./model/*.h)
MODEL_OBJ = $(patsubst %.cpp, %.o, $(MODEL_SRC))
MODEL_OBJ_COV = $(patsubst %.cpp, %.o_cov, $(MODEL_SRC))
TEST_SRC = $(wildcard ./tests/*.cpp)
TEST_H = $(wildcard ./tests/*.h)
TEST_OBJ = $(patsubst %.cpp, %.o, $(TEST_SRC))

TEST_BUILD_DIR = build_test
CMEMTEST = valgrind --leak-check=full --track-origins=yes
TEST_FILE = model_test
CLIB = s21_calculator_model.a
CLIB_DIR = libs

QMAKE = qmake
CMAKE = cmake
OUTPUT_DIR = SmartCalc_v2.0
APP_LABEL = SmartCalc_v2
APP_OUTPUT_QMAKE = view/SmartCalc_v2
APP_OUTPUT_CMAKE = view/SmartCalc_v2
FONT_DIR = ~/.local/share/fonts/
OPENER = xdg-open

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
APP_OUTPUT_QMAKE = view/SmartCalc_v2.app/Contents/MacOS/SmartCalc_v2
APP_OUTPUT_CMAKE = view/SmartCalc_v2.app/Contents/MacOS/SmartCalc_v2
FONT_DIR = ~/Library/Fonts/
OPENER = open
CMEMTEST = leaks -atExit --
endif

.PHONY: all install qmake_install cmake_install run uninstall dist dvi dv_rus gcov_report test style memtest memtest_app clean dist_clean libs rebuild s21_calculator_model.a s21_calculator_model_cov.a style_fix font

# Main targets

all: install run

install:
	$(MAKE) qmake_install || $(MAKE) cmake_install

qmake_install: clean libs font
	cd view && $(QMAKE) && $(MAKE)
	mkdir -p $(OUTPUT_DIR)
	mv $(APP_OUTPUT_QMAKE) $(OUTPUT_DIR)/

cmake_install: clean libs font
	cd view && $(CMAKE) -S . -B .
	cd view && $(CMAKE) --build .
	mkdir -p $(OUTPUT_DIR)
	mv $(APP_OUTPUT_CMAKE) $(OUTPUT_DIR)/

run:
	./$(OUTPUT_DIR)/$(APP_LABEL)

uninstall:
	rm -rf ./$(OUTPUT_DIR)

dist: clean distclean
	tar -cf SmartCalc_v2.0.tar view model controller misc tests CMakeLists.txt Makefile ../README.md ../README_RUS.md

dvi:
	$(OPENER) ../README.md

dvi_rus:
	$(OPENER) ../README_RUS.md

gcov_report: test
	lcov -t "S21CalculatorCPP" -o s21_calculator_model.info -c -d ./model/
	lcov -r s21_calculator_model.info '/usr/include/*' -o s21_calculator_model.info
	genhtml -o report s21_calculator_model.info
	$(OPENER) ./report/index.html

test: s21_calculator_model_cov.a
	$(CMAKE) -S . -B $(TEST_BUILD_DIR)
	$(CMAKE) --build $(TEST_BUILD_DIR)
	mv ./$(TEST_BUILD_DIR)/$(TEST_FILE) ./
	./$(TEST_FILE)

style: clean
	clang-format -style=Google -n $(MODEL_SRC) $(MODEL_H) $(TEST_SRC) $(TEST_H) $(UI_SRC) $(CONTROLLER_SRC)

memorytest: clean test
	$(CMEMTEST) ./$(TEST_FILE)

clean:
	rm -rf $(TEST_FILE)
	rm -f ./*.o ./*.o_cov ./tests/*.o ./*.a ./model/*.o_cov ./model/*.o
	rm -rf ./*.gcda ./*.gcno ./*.info ./model/*.gcda ./model/*.gcno ./model/*.info
	rm -rf ./report/
	rm -rf ./$(TEST_BUILD_DIR)
	rm -rf ./$(CLIB_DIR)
	rm -rf view/.qmake.stash view/Makefile view/moc_*
	rm -rf view/ui_*.h view/*.o view/$(APP_LABEL).app view/qrc_resource.cpp
	rm -rf view/SmartCalc_v2_autogen view/CMakeFiles view/*.cmake view/*Cache.txt

distclean:
	rm -rf SmartCalc_v2.0.tar

rebuild: clean all

# Misc targets

libs: s21_calculator_model.a

s21_calculator_model.a: $(MODEL_OBJ)
	rm -rf $(CLIB_DIR)/$(CLIB)
	mkdir -p $(CLIB_DIR)
	ar -rs $(CLIB_DIR)/$(CLIB) $(MODEL_OBJ)

s21_calculator_model_cov.a: $(MODEL_OBJ_COV)
	rm -rf $(CLIB_DIR)/$(CLIB)
	mkdir -p $(CLIB_DIR)
	ar -rs $(CLIB_DIR)/$(CLIB) $(MODEL_OBJ_COV)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

%.o_cov: %.cpp
	$(CC) --coverage $(CFLAGS) -c $< -o $@

font:
	mkdir -p $(FONT_DIR)
	cp misc/fonts/Anta-Regular.ttf $(FONT_DIR)
	cp misc/fonts/KodeMono-VariableFont_wght.ttf $(FONT_DIR)
ifeq ($(UNAME_S), Linux)
	fc-cache -fv $(FONT_DIR)
endif

style_fix: clean
	clang-format -style=Google -i $(MODEL_SRC) $(MODEL_H) $(TEST_SRC) $(TEST_H) $(UI_SRC) $(CONTROLLER_SRC)
