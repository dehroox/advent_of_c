#include <sys/cdefs.h>

// GTFO PULLING IN ENTIRE HEADER FILES FOR 1 OR 2 MACROS
extern int printf(const char *__restrict __format, ...);
extern int strcmp(const char *__s1, const char *__s2) __THROW __attribute_pure__
    __nonnull((1, 2));
extern int atoi(const char *__nptr) __THROW __attribute_pure__
    __nonnull((1)) __wur;

#define BHRED "\033[1;91m"
#define COLOR_RESET "\033[0m"
int DAY_1(void) { return 0; }
int DAY_2(void) { return 0; }
int DAY_3(void) { return 0; }
int DAY_4(void) { return 0; }
int DAY_5(void) { return 0; }
int DAY_6(void) { return 0; }
int DAY_7(void) { return 0; }
int DAY_8(void) { return 0; }
int DAY_9(void) { return 0; }
int DAY_10(void) { return 0; }
int DAY_11(void) { return 0; }
int DAY_12(void) { return 0; }
int DAY_13(void) { return 0; }
int DAY_14(void) { return 0; }
int DAY_15(void) { return 0; }
int DAY_16(void) { return 0; }
int DAY_17(void) { return 0; }
int DAY_18(void) { return 0; }
int DAY_19(void) { return 0; }
int DAY_20(void) { return 0; }
int DAY_21(void) { return 0; }
int DAY_22(void) { return 0; }
int DAY_23(void) { return 0; }
int DAY_24(void) { return 0; }
int DAY_25(void) { return 0; }

typedef int (*FunctionPointer)(void);
const FunctionPointer DAYS[25] = {&DAY_1,  &DAY_2,  &DAY_3,  &DAY_4,  &DAY_5,
                                  &DAY_6,  &DAY_7,  &DAY_8,  &DAY_9,  &DAY_10,
                                  &DAY_11, &DAY_12, &DAY_13, &DAY_14, &DAY_15,
                                  &DAY_16, &DAY_17, &DAY_18, &DAY_19, &DAY_20,
                                  &DAY_21, &DAY_22, &DAY_23, &DAY_24, &DAY_25};

int run(int day) {
  if (DAYS[day])
    return DAYS[day]();

  printf("\nUnhandled Day: %i\n", day);
  return 1;
}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    run(atoi(argv[1]));
    return 0;
  }

  printf("%s\nAdvent of C\n\nUsage:\n  aoc [day]\n\n%s", BHRED, COLOR_RESET);
  return 1;
}
