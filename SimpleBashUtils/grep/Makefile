FLAGS = -Wall -Werror -Wextra -std=c11

all: clean build

build: s21_grep

s21_grep: s21_grep.c
	gcc $(FLAGS) s21_grep.c -o s21_grep

test: s21_grep
	chmod +x test_grep.sh
	./test_grep.sh
	make clean

clean:
	rm -rf s21_grep a.out