CFLAGS = gcc -c -Wall -Werror -Wextra -std=c11
TFLAGS = gcc -std=c11
GVFLAGS = -L. -ls21_string --coverage
OS := $(shell uname)

ifeq ($(OS), Linux)
	CHECK_FLAGS = -pthread -lrt -lm -lsubunit -lcheck
else
	CHECK_FLAGS = -lcheck libs21_string.a
endif

COMPILE = $(TFLAGS) test.c libs21_string.a $(CHECK_FLAGS) -L. -ls21_string

all: s21_string.a gcov_report test

test: s21_string.a 
	$(COMPILE)
	./a.out

gcov_report: s21_string.a test
	rm -f *.g*
	$(TFLAGS) s21_*.c test.c libs21_string.a $(CHECK_FLAGS) $(GVFLAGS)
	./a.out
	lcov -t a.out -o rep.info -c -d .
	genhtml -o report rep.info
	open ./report/index.html

s21_string.a: s21_string.o
	ar rcs libs21_string.a *.o
	ranlib libs21_string.a
	cp libs21_string.a s21_string.a
	cp libs21_string.a ls21_string.a

s21_string.o:
	$(CFLAGS) -c s21*.c
clean:
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./test && rm -rf ./gcov_report
	-rm -rf ./report/
	-rm -rf s21_test
	-rm -rf ./a.out

rebuild: clean all