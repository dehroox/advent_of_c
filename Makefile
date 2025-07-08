release_native:
	clang -O3 -pipe -Wall -Wpedantic -Wextra -march=native -flto src/main.c -o out/aoc