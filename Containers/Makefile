CXXFLAGS = -std=c++20 -Wall -Werror -Wextra -g
LDFLAGS = --coverage -lgtest -pthread

.PHONY: all test clean gcov_report valgrind clang

all: clean test

test: test.o
	@g++ test.o $(CXXFLAGS) $(LDFLAGS) -o test
	@./test

test.o: test.cpp
	@g++ -c test.cpp $(CXXFLAGS) $(LDFLAGS) -o test.o

lcov_report: test
	@lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch > /dev/null 2>&1
	@lcov --extract coverage.info 'src/*' --output-file coverage_filtered.info > /dev/null 2>&1
	@genhtml coverage_filtered.info --output-directory coverage_report > /dev/null 2>&1
	@xdg-open coverage_report/index.html > /dev/null 2>&1

clean:
	@rm -rf test test.o test.gcda test.gcno coverage.info coverage_report coverage_filtered.info

valgrind: all
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

clang:
	@cp ../materials/linters/.clang-format .clang-format
	@clang-format -n containers/*.h containers_plus/*.h *.h *.cpp
	@clang-format -i containers/*.h containers_plus/*.h *.h *.cpp
	@rm .clang-format