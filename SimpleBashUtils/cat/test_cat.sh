#!/bin/bash

test () {
    local test_name="$1"
    local option="$2"
    local file1="$3"
    local file2="$4"
    local file="$5"

    if diff "$file1" "$file2" > /dev/null; then
        printf "Test %s: Success\n" "$test_name"
    else
        printf "\n"
        printf "Test %s: Failed\n" "$test_name"
        echo "Cat output:"
        cat "$option" "$file"
        echo "s21_cat output:"
        ./s21_cat "$option" "$file"
        printf "\n"
    fi
}

echo "Start test"

echo -e "Hello\nWorld\nSchool21" > test.txt
cat -b test.txt > test1.txt 2>/dev/null
./s21_cat -b test.txt > test2.txt
test "-b" -b test1.txt test2.txt test.txt

echo -e "Hello World\t\n\nThis line\nThis line\rHello again" > test.txt
cat -e test.txt > test1.txt 2>/dev/null
./s21_cat -e test.txt > test2.txt
test "-e" -e test1.txt test2.txt test.txt

echo -e "Hello\nWorld\n\n\nSchool21" > test.txt
cat -n test.txt > test1.txt 2>/dev/null
./s21_cat -n test.txt > test2.txt
test "-n" -n test1.txt test2.txt test.txt

echo -e "Hello\nWorld\n\n\n\n\n\n\nSchool21" > test.txt
cat -s test.txt > test1.txt 2>/dev/null
./s21_cat -s test.txt > test2.txt
test "-s" -s test1.txt test2.txt test.txt

echo -e "Hello World\t\n\nThis line\nThis line\rHello again" > test.txt
cat -t test.txt > test1.txt 2>/dev/null
./s21_cat -t test.txt > test2.txt
test "-t" -t test1.txt test2.txt test.txt

echo -e "Hello World\t\n\nThis line\nThis line\rHello again" > test.txt
cat -E test.txt > test1.txt 2>/dev/null
./s21_cat -E test.txt > test2.txt
test "-E" -E test1.txt test2.txt test.txt

echo -e "Hello World\t\n\nThis line\nThis line\rHello again" > test.txt
cat -T test.txt > test1.txt 2>/dev/null
./s21_cat -T test.txt > test2.txt
test "-T" -T test1.txt test2.txt test.txt

echo -e "Hello\nWorld\nSchool21" > test.txt
cat --number-nonblank test.txt > test1.txt 2>/dev/null
./s21_cat --number-nonblank test.txt > test2.txt
test "--number-nonblank" --number-nonblank test1.txt test2.txt test.txt

echo -e "Hello\n\nWorld\nSchool21" > test.txt
cat --number test.txt > test1.txt 2>/dev/null
./s21_cat --number test.txt > test2.txt
test "--number" --number test1.txt test2.txt test.txt

echo -e "Hello\n\n\nWorld\nSchool21" > test.txt
cat --squeeze-blank test.txt > test1.txt 2>/dev/null
./s21_cat --squeeze-blank test.txt > test2.txt
test "--squeeze-blank" --squeeze-blank test1.txt test2.txt test.txt

rm test.txt test1.txt test2.txt