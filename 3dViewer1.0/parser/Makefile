FLAGS = -lcheck -lm -lpthread
SOURCES=s21_matrix.c parser.c
OBJECTS=s21_matrix.o parser.o
BUILD=make
DIST_TARGETS=README.md ./src/parser/s21_matrix.c ./src/parser/parser.c ./src/parser/cube.obj.zip ./src/parser/test.c ./src/parser/s21_matrix.h ./src/parser/parser.h ./src/CMakeLists.txt ./src/main.cpp ./src/mainwindow.h ./src/widget.h ./src/gifmaker ./src/mainwindow.cpp ./src/mainwindow.ui ./src/widget.cpp ./src/Архив.zip

ifeq ($(shell uname -s), Linux)
	LFLAGS = -lm -lpthread -lcheck -lsubunit
endif

.PHONY: all
all: uninstall install

.PHONY: tests
tests: gpt_help.a s21_matrix.a
	tar -xvf cube.obj.zip
	gcc $(FLAGS) -c test.c
	gcc test.o $(FLAGS) $(OBJECTS) $(LFLAGS) -L. gpt_help.a s21_matrix.a -o test
	rm -rf *.o
gpt_help.a:
	gcc $(FLAGS) -c $(SOURCES)
	ar rcs gpt_help.a $(OBJECTS)
	ranlib gpt_help.a

s21_matrix.a : s21_matrix.o
	ar rc libs21_matrix.a *.o
	ranlib libs21_matrix.a
	cp libs21_matrix.a s21_matrix.a

s21_matrix.o:
	gcc ${CFLAGS} -c ${SOURCES}

.PHONY: style
style:
	clang-format -style=Google -n *.c *.h
	cd .. && clang-format -style=Google -n *.cpp *.h

.PHONY: install
install:
	mkdir build
	mkdir $(HOME)/Desktop/viewer
	mkdir $(HOME)/Desktop/viewer/models
	tar -xvf ../Архив.zip
	cp -rf heart.obj $(HOME)/Desktop/viewer/models
	cp -rf FullSword.obj $(HOME)/Desktop/viewer/models
	cp -rf Ball.obj $(HOME)/Desktop/viewer/models
	cd build && cmake ../../CMakeLists.txt && ${BUILD}
	cp -rf build/gpt_help.app $(HOME)/Desktop/viewer/3DViewer.app
	rm -rf heart.obj FullSword.obj Ball.obj

.PHONY: uninstall
uninstall: clean
	rm -rf build
	rm -rf ../gpt_help.app
	rm -rf ../CMakeFiles
	rm -rf ../Makefile
	rm -rf ../CMakeCache.txt
	rm -rf ../cmake_install.cmake
	rm -rf $(HOME)/Desktop/viewer
	rm -rf heart.obj FullSword.obj Ball.obj

.PHONY: gcov_report
gcov_report: clean add_coverage test
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

.PHONY: dist
dist:
	cd ../.. && mkdir dist && cp -r ${DIST_TARGETS} dist
	cp -r ../../dist . 
	tar -czvf dist.tar.gz dist
	rm -rf ../../dist 
	rm -rf dist

.PHONY: dvi
dvi:
	doxygen Doxyfile
	open ./html/index.html/


.PHONY: clean
clean:
	rm -rf *.o gcov_report *.a *.gcda *.gcno html cube.obj ../../*.gz test test.info -r report 

add_coverage:
	$(eval FLAGS += --coverage)

