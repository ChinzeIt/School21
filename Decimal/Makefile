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
FILES_C_SUP = support_func/s21_*.c
FILES_O = s21_*.o

all: s21_decimal.a

s21_decimal.a:
	$(CC) $(CFLAGS) -c $(FILES_C) $(FILES_C_SUP)
	ar rc s21_decimal.a $(FILES_O)
	ranlib s21_decimal.a
	rm $(FILES_O)

test: s21_decimal.a
	$(CC) test_decimal.c $(FILES_C) $(FILES_C_SUP) s21_decimal.a -o test $(CLIBS)
	./test

gcov_report: s21_decimal.a 
	mkdir logs
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage s21_decimal.a test_decimal.c $(FILES_C) $(FILES_C_SUP) -o logs/gcov_report $(CLIBS)
	./logs/gcov_report
	gcovr --html-details --gcov-exclude test_decimal.c -o logs/report.html
	open logs/report.html 

lcov_rep: s21_decimal.a 
	mkdir logs_lcov
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage s21_decimal.a test_decimal.c $(FILES_C) $(FILES_C_SUP) -o logs_lcov/gcov_test $(CLIBS)
	./logs_lcov/gcov_test
	lcov -t "Tests coverage" -o logs_lcov/gcov_test.info -c -d .
	genhtml -o report logs_lcov/gcov_test.info
	open report/index.html

clean:
	rm -rf *.o *.a test logs logs_lcov *.gcda *.gcno coverage.info gcov_test.info gcov_test report/

rebuild: clean all

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c support_func/*.c *.h support_func/*.h
	clang-format -i *.c support_func/*.c *.h support_func/*.h
	rm -f .clang-format

cpp:
	cppcheck --enable=all $(FILES_C) $(FILES_C_SUP) --suppress=unusedFunction --suppress=missingIncludeSystem  s21_decimal.h suppor_func/s21_decimal_support_func.h
