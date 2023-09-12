FLAGS = -Wall -Werror -Wextra -std=c11
LFLAGS = -lcheck -lm -lpthread
HEADERS = s21_decimal.h

TESTS = $(wildcard tests/*.c)

SOURCES_ALL = s21_support_functions.c	\
	$(wildcard ./conversion/s21*.c) 	\
	$(wildcard ./rounding/s21*.c) 		\
	$(wildcard ./arithmetic/s21*.c) 	\
	$(wildcard ./comparison/*.c)


OBJ_LIBRARY := $(patsubst %.c, %.o, $(SOURCES_ALL))

ifeq ($(shell uname -s), Linux)
	LFLAGS = -lpthread -lcheck -lm -lsubunit
endif


%.o: %.c $(HEADER)
	gcc $(CFLAGS) -c $< -o $@

all: clean s21_decimal.a

test: s21_decimal.a
	gcc $(FLAGS) $(TESTS) $(SOURCES_ALL) $(LFLAGS) -L. s21_decimal.a -o test
	rm -rf *.o

s21_decimal.a: $(OBJ_LIBRARY) $(HEADERS)
	ar rcs s21_decimal.a $(OBJ_LIBRARY)
	ranlib s21_decimal.a
	rm -rf ./*/*.o

gcov_report: clean add_coverage test
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

clean:
	rm -rf *.o gcov_report *.a *.gcda *.gcno test test.info
	rm -rf report

add_coverage:
	$(eval FLAGS += --coverage)