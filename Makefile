name: C Test & Coverage

on: [push, pull_request]

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4

      - name: Install dependencies
        run: sudo apt-get update && sudo apt-get install -y gcc gcov lcov

      - name: Build with coverage flags
        run: make

      - name: Run tests
        run: make run

      - name: Collect lcov coverage
        run: |
          lcov --capture --directory . --output-file coverage.info
          lcov --extract coverage.info "$(pwd)/calculator.c" --output-file coverage.info
          genhtml coverage.info --output-directory coverage-report

      - name: Deploy coverage to GitHub Pages
        uses: peaceiris/actions-gh-pages@v4
        with:
          github_token: ${{ secrets.GITHUB_TOKEN }}
          publish_dir: ./coverage-report