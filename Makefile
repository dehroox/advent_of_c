dev_native:
	clang -O0 -Wall -Wpedantic -Wextra -march=native src/main.c -o out/aoc_dev

release_native:
	clang -O3 -pipe -Wall -Wpedantic -Wextra -march=native -flto src/main.c -o out/aoc
