#include <bits/types/struct_iovec.h>
#include <sys/cdefs.h>
#include <sys/types.h>

// GTFO PULLING IN ENTIRE HEADER FILES FOR 1 OR 2 MACROS
extern ssize_t readv(int __fd, const struct iovec *__iovec, int __count) __wur
    __attr_access((__read_only__, 2, 3));
extern int printf(const char *__restrict __format, ...);
extern int strcmp(const char *__s1, const char *__s2) __THROW __attribute_pure__
    __nonnull((1, 2));
extern int atoi(const char *__nptr) __THROW __attribute_pure__
    __nonnull((1)) __wur;

#define BHRED "\033[1;91m"
#define COLOR_RESET "\033[0m"
char *DAY_1(void) { return "X"; }
char *DAY_2(void) { return "X"; }
char *DAY_3(void) { return "X"; }
char *DAY_4(void) { return "X"; }
char *DAY_5(void) { return "X"; }
char *DAY_6(void) { return "X"; }
char *DAY_7(void) { return "X"; }
char *DAY_8(void) { return "X"; }
char *DAY_9(void) { return "X"; }
char *DAY_10(void) { return "X"; }
char *DAY_11(void) { return "X"; }
char *DAY_12(void) { return "X"; }
char *DAY_13(void) { return "X"; }
char *DAY_14(void) { return "X"; }
char *DAY_15(void) { return "X"; }
char *DAY_16(void) { return "X"; }
char *DAY_17(void) { return "X"; }
char *DAY_18(void) { return "X"; }
char *DAY_19(void) { return "X"; }
char *DAY_20(void) { return "X"; }
char *DAY_21(void) { return "X"; }
char *DAY_22(void) { return "X"; }
char *DAY_23(void) { return "X"; }
char *DAY_24(void) { return "X"; }
char *DAY_25(void) { return "X"; }

typedef char *(*FunctionPointer)(void);
const FunctionPointer DAYS[25] = {&DAY_1,  &DAY_2,  &DAY_3,  &DAY_4,  &DAY_5,
                                  &DAY_6,  &DAY_7,  &DAY_8,  &DAY_9,  &DAY_10,
                                  &DAY_11, &DAY_12, &DAY_13, &DAY_14, &DAY_15,
                                  &DAY_16, &DAY_17, &DAY_18, &DAY_19, &DAY_20,
                                  &DAY_21, &DAY_22, &DAY_23, &DAY_24, &DAY_25};

char *run(int day) {
  if (DAYS[day])
    return DAYS[day]();

  return "Unhandled Day";
}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    printf("\n%s\n", run(atoi(argv[1])));
    return 0;
  }

  printf("%s\nAdvent of C\n\nUsage:\n  aoc [day]\n\n%s", BHRED, COLOR_RESET);
  return 1;
}
