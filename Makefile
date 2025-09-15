CC=gcc
CFLAGS=-fprofile-arcs -ftest-coverage -I.
SRC=calculator.c test_calculator.c unity.c
OUT=test_runner

all: $(OUT)

$(OUT): $(SRC)
    $(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
    ./$(OUT)

coverage: run
    lcov --capture --directory . --output-file coverage.info
    lcov --extract coverage.info "$(PWD)/calculator.c" --output-file coverage.info
    genhtml coverage.info --output-directory coverage-report
    @echo 'Open coverage report with: "$$BROWSER" coverage-report/index.html'

open-coverage: coverage
    "$(BROWSER)" coverage-report/index.html

clean:
    rm -f $(OUT) *.gcda *.gcno *.gcov coverage.info
    rm -rf coverage-report