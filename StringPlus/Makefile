CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    CLIBS=-lcheck -lm -lsubunit -lpthread
endif

ifeq ($(UNAME_S),Darwin)
    CLIBS=-lcheck -lm
endif


FILES_C = s21_*.c
FILES_O = s21_*.o

all: s21_string.a

s21_string.a:
	$(CC) $(CFLAGS) -c $(FILES_C)
	ar rc s21_string.a $(FILES_O)
	ranlib s21_string.a
	rm $(FILES_O)

test: s21_string.a
	$(CC) test_string.c $(FILES_C) s21_string.a -o test $(CLIBS)
	./test

gcov_report: s21_string.a 
	mkdir logs
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage s21_string.a test_string.c $(FILES_C) -o logs/gcov_report $(CLIBS)
	./logs/gcov_report
	gcovr --html-details --gcov-exclude test_string.c -o logs/report.html
	open logs/report.html 

lcov_rep: s21_string.a 
	mkdir logs_lcov
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage s21_string.a test_string.c $(FILES_C) -o logs_lcov/gcov_test $(CLIBS)
	./logs_lcov/gcov_test
	lcov -t "Tests coverage" -o logs_lcov/gcov_test.info -c -d .
	genhtml -o report logs_lcov/gcov_test.info
	open report/index.html

clean:
	rm -rf *.o *.a test logs logs_lcov *.gcda *.gcno coverage.info gcov_test.info gcov_test report/

rebuild: clean all

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c 
	clang-format -i *.c 
	rm .clang-format

cpp:
	cppcheck --enable=all $(FILES_C) --suppress=unusedFunction --suppress=missingIncludeSystem  s21_string.h s21_sprintf.h s21_sscanf.h
