dev:
	clang -O0 -g -Wall -Wpedantic -Wextra -march=native src/*.c -o out/aoc_dev
release_native:
	clang -O3 -pipe -Wall -Wpedantic -Wextra -march=native -flto src/*.c -o out/aoc

