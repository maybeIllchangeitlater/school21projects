COMPILER = g++
FLAGS = -std=c++17 -Wall -Werror -Wextra
TARGETS = s21_matrix_oop.cc
GCOV = -fprofile-arcs -ftest-coverage -fPIC -pthread
GTEST = -lgtest -lgtest_main

all: gcov_report

.PHONY: gcov_report
gcov_report: test
	lcov -t "matrix" -o matrix.info -c -d .
	genhtml -o report matrix.info
	open report/index.html

.PHONY: test
test: clean
	${COMPILER} ${FALGS} tests_matrix_oop.cc -c
	${COMPILER} ${FLAGS} ${GCOV} ${TARGETS} tests_matrix_oop.o -o test ${GTEST}
	./test

.PHONY: style
style:
	cp ./../materials/linters/.clang-format ./
	clang-format -i *.cc *.h
	rm .clang-format

.PHONY: s21_matrix_oop.a
s21_matrix_oop.a : s21_matrix_oop.o
	ar rc libs21_matrix_oop.a *.o
	ranlib libs21_matrix_oop.a
	cp libs21_matrix_oop.a s21_matrix_oop.a

.PHONY: s21_matrix_oop.o
s21_matrix_oop.o:
	${COMPILER} ${FLAGS} -c  ${TARGETS}

.PHONY: clean
clean:
	rm -rf *.o *.out *.gch *.dSYM *.gcov *.gcda *.gcno *.a tests_s21_matrix *.css *.html vgcore* report *.info *.gz *.log test

#forleaks - open docker desktop, run docker run -tiv $PWD/:/valgrind karek/valgrind:latest, complie, run valgrind --leak-check=full ./test
