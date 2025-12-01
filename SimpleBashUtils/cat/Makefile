FLAGS = -Wall -Werror -Wextra -std=c11

all: clean build

build: s21_cat

s21_cat: s21_cat.c
	gcc $(FLAGS) s21_cat.c -o s21_cat

test: s21_cat
	chmod +x test_cat.sh
	./test_cat.sh
	make clean

clean:
	rm -rf s21_cat a.out