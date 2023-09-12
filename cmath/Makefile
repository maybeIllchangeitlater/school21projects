CFLAGS = gcc -c -Wall -Werror -Wextra -std=c11
TFLAGS = gcc -std=c11
GVFLAGS = -L. -ls21_math --coverage
OS := $(shell uname)

ifeq ($(OS), Linux)
	CHECK_FLAGS = -pthread -lrt -lm -lsubunit -lcheck
else
	CHECK_FLAGS = -lcheck libs21_math.a
endif

COMPILE = $(TFLAGS) test.c libs21_math.a $(CHECK_FLAGS) -L. -ls21_math

all: s21_math.a gcov_report test

test: s21_math.a 
	$(COMPILE)
	./a.out

gcov_report: s21_math.a test
	rm -f *.g*
	$(TFLAGS) s21_*.c test.c libs21_math.a $(CHECK_FLAGS) $(GVFLAGS)
	./a.out
	lcov -t a.out -o rep.info -c -d .
	genhtml -o report rep.info
	open ./report/index.html

s21_math.a: s21_math.o
	ar rcs libs21_math.a *.o
	ranlib libs21_math.a
	cp libs21_math.a s21_math.a
	cp libs21_math.a ls21_math.a

s21_math.o:
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
