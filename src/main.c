#include "colors.h"
#include <sys/cdefs.h>

// GTFO PULLING IN ENTIRE HEADER FILES FOR 1 OR 2 MACROS
extern int printf(const char *__restrict __format, ...);
extern int strcmp(const char *__s1, const char *__s2) __THROW __attribute_pure__
    __nonnull((1, 2));

#define println printf("%s\n")

int run(char *year_day) {
  if (strcmp(year_day, "2024-1") == 0) {
    printf("Hello World!\n");
  } else {
    printf("\nUnhandled Year/Day: %s\n", year_day);
    return 1;
  };
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    char *year_day = argv[1];

    printf("Starting day:  %s\n", year_day);
    run(year_day);
  } else {
    printf("%s\nAdvent of C\n\nUsage:\n  aoc [year]-[day]\n\n%s", BHRED,
           COLOR_RESET);
    return 1;
  };
  return 0;
}
