# src/Makefile

CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic
CHECK_FLAGS = -lcheck -lsubunit -lm -L.


ifeq ($(strip $(DESTDIR)),)
	INSTALL_DIR = /usr/bin
else
	INSTALL_DIR = $(DESTDIR)
endif


all: allert test gcov_report install;
# this should compile and test the program

install: build ;
# make DESTDIR=/home/user/Desktop install 
	cp gui/3dViewer $(INSTALL_DIR)

uninstall: ;
	cd $(INSTALL_DIR); rm -f 3dViewer

clean: ;
	cd gui; make clean
	rm -f gui/3dViewer gui/Makefile
	rm -f proj* val* *.dvi 3d* *.bin
	rm -rf report

dvi: 3d_viewer.dvi ;
#  generates documentation in given format

3d_viewer.dvi: manual.texi
#	makeinfo --html --no-split -o 3d_viewer.html manual.texi 
	texi2dvi manual.texi -o 3d_viewer.dvi
	rm *.log *.aux *.toc

q_make: ;
	@cd gui; qmake

build: clean q_make ;
	@cd gui; make
	@sleep 5
	@cd gui; make clean

dist: clean ;
	rm -rf 3d_viewer/ && rm -f 3d_viewer.tar.gz
	mkdir 3d_viewer && mkdir 3d_viewer/src && mkdir 3d_viewer/src/img
	cp *.texi *.c *.h makefile .clang-format 3d_viewer/src
	cp -R gui 3d_viewer/src
	cp img/a*.* 3d_viewer/src/img
	tar -czvf 3d_viewer.tar.gz 3d_viewer/src
	rm -rf 3d_viewer/

test: clean ;
	@echo ------- test: -------
	gcc test.c logic.c -o project_test $(CHECK_FLAGS) $(CFLAGS)
	./project_test

gcov_report: clean ;
	@echo ------- gcov_report: -------
	gcc test.c logic.c -o project_gcov $(CHECK_FLAGS) $(CFLAGS) --coverage
	@./project_gcov > project.txt
	lcov -t "gcov_testing" -o project.info -c -d . && rm -f *.gc*
	genhtml -o report project.info
#	open ./report/index.html

valgrind: test ;
	@echo ------- valgrind: -------
	valgrind -s --log-file="valgrind.txt" --tool=memcheck --leak-check=full --track-origins=yes ./project_test
	@grep "ERROR SUMMARY:" valgrind.txt

make_style: ;
	clang-format -i *.c *.h gui/*.h gui/*.cpp

style: ;
	clang-format -n *.c *.h gui/*.h gui/*.cpp

allert: ;
	@echo 'Перед сборкой программы убедитесь в наличии необходимых библиотек qt.'
	@sleep 7

.PHONY: all allert clean style test
.IGNORE: allert clean style
