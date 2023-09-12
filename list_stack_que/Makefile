CXX = g++
FLAGS = -std=c++17 -Wall -Werror -Wextra
SANITIZE = -fsanitize=address -pedantic
TARGETS = test.cc
GCOV = -fprofile-arcs -ftest-coverage -fPIC -pthread
GTEST = -lgtest -lgtest_main

all: test

test: clean
	${CXX} ${TARGETS} ${FLAGS} ${GCOV} ${GTEST} -o test
	./test

test_asan: clean
	${CXX} ${FLAGS} ${SANITIZE} ${TARGETS} ${GTEST} -o test_asan
	./test_asan


gcov_report: test
	mkdir report
	gcovr --html-details -o report/coverage.html
	open ./report/coverage.html

style:
	clang-format -style=Google -n *.h


clean:
	rm -rf *.o *.out *.gch *.dSYM *.gcov *.gcda *.gcno *.a *.css *.html *.info test test_asan report
.PHONY: test test_asan clean gcov_report style
