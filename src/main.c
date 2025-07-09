#include "read_file.h"
#include "radix_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <time.h>

#define BHRED "\033[1;91m"
#define COLOR_RESET "\033[0m"

char *DAY_1(void) {
#define MAX_LINES 1000
  size_t size;
  char *data = read_file("./input/a", &size);

  int left[MAX_LINES] __attribute__((aligned(64)));
  int right[MAX_LINES] __attribute__((aligned(64)));

  char *data_copy = strdup(data);
  char *line = strtok(data_copy, "\n");
  int index = 0;

  while (line != NULL && index < MAX_LINES) {
    char *end_ptr;

    left[index] = (int)strtoul(line, &end_ptr, 10);

    right[index] = (int)strtoul(end_ptr, NULL, 10);

    ++index;
    line = strtok(NULL, "\n");
  }

  free(data_copy);
  munmap(data, size);

  radix_sort(left, 0, 1000, 24);
  radix_sort(right, 0, 1000, 24);

  int difference = 0;
  for (int i = 0; i < MAX_LINES; ++i) {
    difference += abs(left[i] - right[i]);
  }

  static char final[8];
  snprintf(final, 8, "%d", difference);
  return final;
}

char *DAY_2(void) { return "2"; }
char *DAY_3(void) { return "3"; }
char *DAY_4(void) { return "4"; }
char *DAY_5(void) { return "5"; }
char *DAY_6(void) { return "6"; }
char *DAY_7(void) { return "7"; }
char *DAY_8(void) { return "8"; }
char *DAY_9(void) { return "9"; }
char *DAY_10(void) { return "10"; }
char *DAY_11(void) { return "11"; }
char *DAY_12(void) { return "12"; }
char *DAY_13(void) { return "13"; }
char *DAY_14(void) { return "14"; }
char *DAY_15(void) { return "15"; }
char *DAY_16(void) { return "16"; }
char *DAY_17(void) { return "17"; }
char *DAY_18(void) { return "18"; }
char *DAY_19(void) { return "19"; }
char *DAY_20(void) { return "20"; }
char *DAY_21(void) { return "21"; }
char *DAY_22(void) { return "22"; }
char *DAY_23(void) { return "23"; }
char *DAY_24(void) { return "24"; }
char *DAY_25(void) { return "25"; }

typedef char *(*FunctionPointer)(void);

char *run(unsigned int day) {
  static const FunctionPointer DAYS[26] = {
      DAY_1,  DAY_2,  DAY_3,  DAY_4,  DAY_5,  DAY_6,  DAY_7,  DAY_8,  DAY_9,
      DAY_10, DAY_11, DAY_12, DAY_13, DAY_14, DAY_15, DAY_16, DAY_17, DAY_18,
      DAY_19, DAY_20, DAY_21, DAY_22, DAY_23, DAY_24, DAY_25};

  --day; // index at 1

  if (day < sizeof(DAYS) / sizeof DAYS[0])
    return DAYS[day]();
  return "Unhandled Day";
}

int main(int argc, char *argv[]) {
  clock_t begin = clock();
  if (argc == 2) {
    char *result = run(atoi(argv[1]));
    printf("%s\n", result);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nSeconds spent: %f\n", time_spent);
    return 0;
  }

  printf("%s\nAdvent of C\n\nUsage:\n  aoc [day]\n\n%s", BHRED, COLOR_RESET);
  return 1;
}
