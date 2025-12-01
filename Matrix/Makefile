CPPFLAGS = -Wall -Werror -Wextra -std=c++20
SRC = s21_matrix_oop.cpp
VALFLAGS = --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes -s

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    GTEST_LIBS = -lgtest -lgtest_main -lpthread -lsubunit
endif

ifeq ($(UNAME_S),Darwin)
    GTEST_LIBS = -lgtest -lgtest_main -lpthread
endif

all: clean s21_matrix_oop.a

s21_matrix_oop.a:
	gcc $(CPPFLAGS) -c $(SRC) -o s21_matrix_oop
	ar rc s21_matrix_oop.a s21_matrix_oop
	ranlib s21_matrix_oop.a
	rm s21_matrix_oop

test: all
	g++ $(CPPFLAGS) test.cpp s21_matrix_oop.a -o test $(GTEST_LIBS)
	./test

clean:
	rm -rf *.o *.a *.txt test

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.cpp *.h
	clang-format -i *.cpp *.h
	rm .clang-format

cpp:
	cppcheck --enable=all --force --suppress=missingIncludeSystem --language=c++ s21_matrix_oop.cpp s21_matrix_oop.h