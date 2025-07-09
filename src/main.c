#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define BHRED "\033[1;91m"
#define COLOR_RESET "\033[0m"

char* read_file(const char* path, size_t* size) {
    int fd = open(path, O_RDONLY | O_CLOEXEC);
    if (fd < 0) return NULL;

    struct stat st;
    if (fstat(fd, &st) < 0) {
        close(fd);
        return NULL;
    }
    *size = st.st_size;

    void* mapped_data = mmap(NULL, *size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);

    return (mapped_data == MAP_FAILED) ? NULL : mapped_data;
}
/*
Copyright 2011 Erik Gorset. All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

      THIS SOFTWARE IS PROVIDED BY Erik Gorset ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL Erik Gorset OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
      ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

      The views and conclusions contained in the software and documentation are
those of the authors and should not be interpreted as representing official
policies, either expressed or implied, of Erik Gorset.
*/

void insertion_sort(int *array, int offset, int end) {
  for (int x = offset + 1; x < end; x++) {
    int temp = array[x];
    int y = x;
    while (y > offset && array[y - 1] > temp) {
      array[y] = array[y - 1];
      y--;
    }
    array[y] = temp;
  }
}

void radix_sort(int *array, int offset, int end, int shift) {
  int x, y, value, temp;
  int last[256] = {0}, pointer[256];

  for (x = offset; x < end; ++x) {
    ++last[(array[x] >> shift) & 0xFF];
  }

  last[0] += offset;
  pointer[0] = offset;
  for (x = 1; x < 256; ++x) {
    pointer[x] = last[x - 1];
    last[x] += last[x - 1];
  }

  for (x = 0; x < 256; ++x) {
    while (pointer[x] != last[x]) {
      value = array[pointer[x]];
      y = (value >> shift) & 0xFF;
      while (x != y) {
        temp = array[pointer[y]];
        array[pointer[y]++] = value;
        value = temp;
        y = (value >> shift) & 0xFF;
      }
      array[pointer[x]++] = value;
    }
  }

  if (shift > 0) {
    shift -= 8;
    for (x = 0; x < 256; ++x) {
      temp = x > 0 ? pointer[x] - pointer[x - 1] : pointer[0] - offset;
      if (temp > 64) {
        radix_sort(array, pointer[x] - temp, pointer[x], shift);
      } else if (temp > 1) {
        // std::sort(array + (pointer[x] - temp), array + pointer[x]);
        insertion_sort(array, pointer[x] - temp, pointer[x]);
      }
    }
  }
}

/**/

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
