#!/bin/bash

make s21_matrix.a
gcc -g tests_s21_matrix.c s21_matrix.a -o test -lcheck -lcheck -lpthread -lm -D_GNU_SOURCE -lrt -lsubunit
valgrind --tool=memcheck --leak-check=yes --log-file=valgrind.txt ./test
grep 'ERROR SUMMARY:' valgrind.txt > error_sum.txt
grep -v 'ERROR SUMMARY: 0' error_sum.txt
echo '___________'
