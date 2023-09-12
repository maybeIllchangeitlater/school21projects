CFLAGS = -Wall -Wextra -Werror -std=c11
GCOV = -fprofile-arcs -ftest-coverage -fPIC
FILES = s21*.c
OS = $(shell uname)

ifeq (${OS}, Linux)
	TEST_FLAGS = -lcheck -pthread -lrt -lm -L.
else
	TEST_FLAGS = -lcheck
endif

all: clean gcov_report

gcov_report: test 
	lcov -t "matrix" -o matrix.info -c -d .
	genhtml -o report matrix.info

ifeq (${OS}, Linux)
	cd report && firefox index.html
else
	cd report && open index.html
endif

test: clean s21_matrix.a
	gcc tests_s21_matrix.c -c
	gcc ${CFLAGS} ${TEST_FLAGS} ${GCOV} ${FILES} tests_s21_matrix.o -o test
	./test

s21_matrix.a : s21_matrix.o
	ar rc libs21_matrix.a *.o
	ranlib libs21_matrix.a
	cp libs21_matrix.a s21_matrix.a

s21_matrix.o: ${FILES}
	gcc ${CFLAGS} -c ${FILES}

style:
	cp ./../materials/linters/.clang-format ./
	clang-format -i *.c *.h
	rm .clang-format

clean:
	rm -rf *.o *.out *.gch *.dSYM *.gcov *.gcda *.gcno *.a tests_s21_matrix *.css *.html vgcore* report *.info *.gz *.log test

rebuild: clean s21_matrix.a

mini_verter:
	cd ../materials/build && sh run.sh

valgrind_test:
	cd ../materials/build/Valgrind/ && sh run.sh

