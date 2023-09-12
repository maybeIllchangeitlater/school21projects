FLAGS = gcc -Wall -Werror -Wextra -std=c11 -pedantic

all: s21_cat

s21_cat: Makefile s21_cat.h s21_cat.c
	$(FLAGS) s21_cat.c -o s21_cat

style: 
	clang-format -style=Google -n *.c

clean: 
	rm -f s21_cat

rebuild: 
	make clean
	make all
