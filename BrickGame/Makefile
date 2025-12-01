CPPFLAGS = -Wall -Wextra -Werror -std=c++20

MAINSRC  :=$(wildcard brick_game/*.c)
MAINSRCH :=$(wildcard brick_game/*.h)

TSRC  := $(wildcard brick_game/tetris/*.c)
SSRC  := $(wildcard brick_game/snake/*.cpp)
TSRCH := $(wildcard brick_game/tetris/*.h)
SSRCH := $(wildcard brick_game/snake/*.h)

CLIFILE := $(wildcard gui/cli/s21_game_field.c gui/cli/s21_border.c gui/cli/s21_caput_field.c gui/cli/s21_choose_game.c gui/cli/s21_initNcurses.c)
DEKFILE := $(wildcard gui/dekstop/*.h)

CLIBS   = -lpthread -lsubunit -lncurses -lm 
VALFLAGS = --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes -s

LDFLAGS = -L. -ltetris -lsnake

MOC = moc
MOCS = moc_mainwindow.cpp moc_view.cpp moc_controller.cpp

moc_mainwindow.cpp: gui/dekstop/s21_mainWindow.h
	@$(MOC) $< -o $@

moc_view.cpp: gui/dekstop/s21_view.h
	@$(MOC) $< -o $@

moc_controller.cpp: gui/dekstop/s21_controller.h
	@$(MOC) $< -o $@

all: clean install
	@echo "|-- CLEAR AND INSTALLED --|"

libtetris.a:
	@g++ $(CPPFLAGS) -c $(TSRC) $(MAINSRC)
	@ar rc libtetris.a *.o
	@ranlib libtetris.a
	@rm -f *.o

libsnake.a:
	@g++ $(CPPFLAGS) -c $(SSRC) $(MAINSRC)
	@ar rc libsnake.a *.o
	@ranlib libsnake.a
	@rm -f *.o

game:
	@mkdir -p game

game/CLI_BrickGame: gui/cli/main.c libtetris.a libsnake.a | game
	@g++ -o $@ $< $(CLIFILE) $(CFLAGS) $(LDFLAGS) $(CLIBS) -pthread

game/BrickGame: gui/dekstop/main.cpp $(MOCS) libtetris.a libsnake.a | game
	@$(MOC) gui/dekstop/s21_mainWindow.h -o moc_mainwindow.cpp
	@$(MOC) gui/dekstop/s21_view.h -o moc_view.cpp
	@$(MOC) gui/dekstop/s21_controller.h -o moc_controller.cpp
	@g++ -o $@ $^ $(CPPFLAGS) $(LDFLAGS) $(CLIBS) -fPIC -pthread `pkg-config --cflags --libs Qt5Widgets`

install: game/CLI_BrickGame game/BrickGame
	@mkdir -p game
	@touch game/scoreTetris.txt game/scoreSnake.txt
	@echo "0" > game/scoreTetris.txt
	@echo "0" > game/scoreSnake.txt
	@echo "|-- INSTALLED --|"

uninstall:
	@rm -rf game *.a $(MOCS)
	@echo "|-- UNINSTALL --|"

clean:
	@rm -rf game/*.o game/valgrind.txt BrickGame.tar.gz test_c test_cpp coverage *.gcda *.gcno *.o  documentation.pdf documentation.aux documentation.log $(MOCS)
	@echo "|-- CLEAN --|"

rebuild: uninstall install
	@echo "|-- REBUILD --|"

test: clean rebuild
	@g++ $(CPPFLAGS) test.c -o test_c -lcheck $(LDFLAGS) $(CLIBS)
	@g++ $(CPPFLAGS) test.cpp -o test_cpp -lgtest -lgtest_main $(LDFLAGS) $(CLIBS)
	@echo "|-- TESTS BUILD --|"

dist: clean rebuild
	@echo "|-- ARCHIVED --|"
	@tar -czf BrickGame.tar.gz Makefile brick_game gui game documentation.tex diagramm_bg.pdf test.c test.cpp
	@echo "|-- RESULT ARCHIVED: BrickGame.tar.gz --|"

dvi: clean
	@echo "|-- MAKE DOC --|"
	@xelatex documentation.tex > /dev/null 2>&1
	@echo "|-- NOW OPEN DOC --|"
	@open documentation.pdf

lcov_report: clean
	@mkdir -p coverage
	@g++ --coverage -fprofile-arcs -ftest-coverage $(CPPFLAGS) -c $(TSRC) $(SSRC) $(MAINSRC)
	@ar rc libtetris.a *.o
	@ar rc libsnake.a *.o
	@ranlib libtetris.a
	@ranlib libsnake.a
	@rm -f *.o
	@g++ --coverage -fprofile-arcs -ftest-coverage $(CPPFLAGS) test.c -o test_c -lcheck $(LDFLAGS) $(CLIBS)
	@g++ --coverage -fprofile-arcs -ftest-coverage $(CPPFLAGS) test.cpp -o test_cpp -lgtest -lgtest_main $(LDFLAGS) $(CLIBS) -pthread
	@./test_c
	@./test_cpp
	@lcov -t "BrickGame_Coverage" -o coverage/coverage.info -c -d . --ignore-errors mismatch,inconsistent,unused,empty
	@lcov -e coverage/coverage.info \
		"brick_game/snake/*" \
		"brick_game/tetris/*" \
		-o coverage/coverage_filtered.info --ignore-errors unused || true
	@genhtml -o coverage/coverage_report coverage/coverage_filtered.info
	@open coverage/coverage_report/index.html 2>/dev/null
	@echo "|-- LCOV REPORT GENERATED --|"

clang:
	@cp ../materials/linters/.clang-format .clang-format
	@clang-format -n $(TSRC) $(TSRCH) $(SSRC) $(SSRCH) $(MAINSRC) $(MAINSRCH) $(CLIFILE) $(DEKFILE) gui/cli/main.c gui/cli/s21_frontend.h gui/dekstop/main.cpp test.c test.cpp
	@clang-format -i $(TSRC) $(TSRCH) $(SSRC) $(SSRCH) $(MAINSRC) $(MAINSRCH) $(CLIFILE) $(DEKFILE) gui/cli/main.c gui/cli/s21_frontend.h gui/dekstop/main.cpp test.c test.cpp
	@rm .clang-format
	@echo "|-- MAKE CLANG --|"

cpp:
	@cppcheck --enable=all $(TSRC) $(SSRC) $(MAINSRC) $(CLIFILE) gui/cli/main.c gui/dekstop/main.cpp --suppress=unusedFunction --suppress=missingIncludeSystem $(TSRCH) $(SSRCH) $(MAINSRCH) $(DEKFILE) gui/cli/s21_frontend.h

valgrind:
	@valgrind $(VALFLAGS) ./game/BrickGame > game/valgrind.txt 2>&1
	@echo "|-- INFO IN game/#valgrind.txt --|"


run_game:
	@LD_PRELOAD=/lib/x86_64-linux-gnu/libpthread.so.0 ./game/BrickGame
