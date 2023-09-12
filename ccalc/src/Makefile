FLAGS = -lcheck -lm -lpthread
SOURCES=s21_*.c
OBJECTS=s21_*.o

ifeq ($(shell uname -s), Linux)
	LFLAGS = -lm -lpthread -lcheck -lsubunit
endif

all: clean ThisTimeForSure.a

test: ThisTimeForSure.a
	gcc $(FLAGS) -c ../datasets/test.c
	gcc test.o $(FLAGS) $(OBJECTS) $(LFLAGS) -L. ThisTimeForSure.a -o test
	rm -rf *.o

ThisTimeForSure.a:
	gcc $(FLAGS) -c $(SOURCES)
	ar rcs ThisTimeForSure.a $(OBJECTS)
	ranlib ThisTimeForSure.a

install:
	mkdir build
	cd build && cmake ../ThisTimeForSure/CMakeLists.txt && make
	cp -rf build/ThisTimeForSure.app $(HOME)/Desktop/Calculator.app

uninstall: clean
	rm -rf build
	rm -rf ThisTimeForSure/ThisTimeForSure.app
	rm -rf ThisTimeForSure/CMakeFiles
	rm -rf ThisTimeForSure/Makefile
	rm -rf ThisTimeForSure/calc_autogen
	rm -rf ThisTimeForSure/CMakeCache.txt
	rm -rf ThisTimeForSure/cmake_install.cmake
	rm -rf $(HOME)/Desktop/Calculator.app

gcov_report: clean add_coverage test
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

dist:
	mkdir ../dist
	cp -r ../src ../dist
	cp ../README.md ../dist
	tar -czvf dist.tar.gz ../dist
	rm -rf ../dist

clean:
	rm -rf *.o gcov_report *.a *.gcda *.gcno test test.info -r report

add_coverage:
	$(eval FLAGS += --coverage)


