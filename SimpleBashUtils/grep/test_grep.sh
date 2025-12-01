#!/bin/bash

test () {
    local test_name="$1"
    local option="$2"
    local pattern="$3"
    local file1="$4"
    local file2="$5"
    local file="$6"

    if diff "$file1" "$file2" > /dev/null; then
        printf "Test %s: Success\n" "$test_name"
    else
        printf "\n"
        printf "Test %s: Failed\n" "$test_name"
        echo "Grep output:"
        grep "$option" "$pattern" "$file"
        echo "s21_grep output:"
        ./s21_grep "$option" "$pattern" "$file"
        printf "\n"
    fi
}

echo "Start test"

echo -e "Hello\nWorld\nSchool21" > test.txt
grep School21 test.txt > test1.txt
./s21_grep School21 test.txt > test2.txt
test " " -e School21 test1.txt test2.txt test.txt

echo -e "Hello\nWorld\nSchool21" > test.txt
grep -e School21 test.txt > test1.txt
./s21_grep -e School21 test.txt > test2.txt
test "-e" -e School21 test1.txt test2.txt test.txt

echo -e "Hello\nWorld\nSchool21" > test.txt
grep -i school21 test.txt > test1.txt
./s21_grep -i school21 test.txt > test2.txt
test "-i" -i School21 test1.txt test2.txt test.txt

echo -e "Hello\nWorld\nSchool21" > test.txt
grep -v School21 test.txt > test1.txt
./s21_grep -v School21 test.txt > test2.txt
test "-v" -v School21 test1.txt test2.txt test.txt

echo -e "Hello\nWorld\nSchool21" > test.txt
grep -c School21 test.txt > test1.txt
./s21_grep -c School21 test.txt > test2.txt
test "-c" -c School21 test1.txt test2.txt test.txt

echo -e "Hello\nWorld\nSchool21" > test.txt
grep -l School21 test.txt > test1.txt
./s21_grep -l School21 test.txt > test2.txt
test "-l" -l School21 test1.txt test2.txt test.txt

echo -e "Hello\nWorld\n School21" > test.txt
grep -n School21 test.txt > test1.txt
./s21_grep -n School21 test.txt > test2.txt
test "-n" -n School21 test1.txt test2.txt test.txt

echo -e "Hello\nWorld\nSchool21" > test.txt
grep -h School21 test.txt > test1.txt
./s21_grep -h School21 test.txt > test2.txt
test "-h" -h School21 test1.txt test2.txt test.txt

echo -e "Hello\nWorld\nSchool21" > test.txt
grep -s School21 te > test1.txt
./s21_grep -s School21 te > test2.txt
test "-s" -s School21 test1.txt test2.txt test.txt

echo -e "Hello\nWorld\nSchool21" > test.txt
echo -e "School21" > testov.txt
grep -f testov.txt test.txt > test1.txt
./s21_grep -f testov.txt test.txt > test2.txt
test "-f" -f School21 test1.txt test2.txt test.txt

echo -e "Hello\nWorld\nSchool21" > test.txt
grep -o 21 test.txt > test1.txt
./s21_grep -o 21 test.txt > test2.txt
test "-o" -o 21 test1.txt test2.txt test.txt

echo -e "Hello\nWorld\nSchool21" > test.txt
grep -in school21 test.txt > test1.txt
./s21_grep -in school21 test.txt > test2.txt
test "-in" -in School21 test1.txt test2.txt test.txt

echo -e "Hello\nWorld\nSchool21" > test.txt
grep -iv school21 test.txt > test1.txt
./s21_grep -iv school21 test.txt > test2.txt
test "-iv" -iv School21 test1.txt test2.txt test.txt

rm test.txt test1.txt test2.txt testov.txt