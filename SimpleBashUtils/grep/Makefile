FLAGS = gcc -Wall -Werror -Wextra -std=c11

all: s21_grep

s21_grep: Makefile s21_grep.h s21_grep.c
	$(FLAGS) s21_grep.c -o s21_grep

style: 
	clang-format -style=Google -n *.c

clean: 
	rm -f s21_grep

rebuild: 
	make clean
	make all
