#include <stddef.h>
#include <sys/stat.h>

#define SYS_OPEN 2
#define SYS_FSTAT 5
#define SYS_MMAP 9
#define SYS_CLOSE 3
#define O_RDONLY 0
#define O_CLOEXEC 02000000
#define PROT_READ 0x1
#define MAP_PRIVATE 0x02
#define MAP_FAILED ((void *)-1)
#define CLOCKS_PER_SEC ((__clock_t)1000000)
#define BHRED "\033[1;91m"
#define COLOR_RESET "\033[0m"

// GTFO PULLING IN ENTIRE HEADER FILES FOR 1 OR 2 MACROS
extern int sprintf(char *__restrict __s, const char *__restrict __format,
                   ...) __THROWNL;

extern int abs(int __x) __THROW __attribute__((__const__)) __wur;

extern void free(void *__ptr) __THROW;

extern __clock_t clock(void) __THROW;

extern char *strdup(const char *__s) __THROW __attribute_malloc__
    __nonnull((1));

extern int printf(const char *__restrict __format, ...);

extern void *malloc(size_t __size) __THROW __attribute_malloc__
    __attribute_alloc_size__((1)) __wur;

extern char *strtok(char *__restrict __s,
                    const char *__restrict __delim) __THROW __nonnull((2));

extern int strcmp(const char *__s1, const char *__s2) __THROW __attribute_pure__
    __nonnull((1, 2));

extern int atoi(const char *__nptr) __THROW __attribute_pure__
    __nonnull((1)) __wur;

extern unsigned long int strtoul(const char *__restrict __nptr,
                                 char **__restrict __endptr, int __base) __THROW
    __nonnull((1));

char *read_file(const char *path) {
  int fd = -1;
  size_t size;
  void *mapped_data = NULL;
  struct stat st;
  register long syscall_ret __asm__("rax");

#define SYSCALL(number, arg1, arg2, arg3)                                      \
  __asm__ __volatile__("syscall"                                               \
                       : "=a"(syscall_ret)                                     \
                       : "a"(number), "D"(arg1), "S"(arg2), "d"(arg3)          \
                       : "rcx", "r11", "memory")

  SYSCALL(SYS_OPEN, path, O_RDONLY | O_CLOEXEC, 0);
  if ((fd = syscall_ret) < 0)
    return NULL;

  SYSCALL(SYS_FSTAT, fd, &st, 0);
  size = st.st_size;

  register long mmap_flags __asm__("r10") = MAP_PRIVATE;
  register long mmap_fd __asm__("r8") = fd;
  register long mmap_offset __asm__("r9") = 0;
  __asm__ __volatile__("syscall"
                       : "=a"(mapped_data)
                       : "a"(SYS_MMAP), "D"(0), "S"(size), "d"(PROT_READ),
                         "r"(mmap_flags), "r"(mmap_fd), "r"(mmap_offset)
                       : "rcx", "r11", "memory");

  SYSCALL(SYS_CLOSE, fd, 0, 0);
  return (mapped_data == MAP_FAILED) ? NULL : mapped_data;

#undef SYSCALL
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
  char *data = read_file("./input/a");

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

  radix_sort(left, 0, 1000, 24);
  radix_sort(right, 0, 1000, 24);

  int difference = 0;
  for (int i = 0; i < MAX_LINES; ++i) {
    difference += abs(left[i] - right[i]);
  }

  static char final[8];
  sprintf(final, "%d", difference);
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
const FunctionPointer DAYS[26] = {&DAY_1,  &DAY_2,  &DAY_3,  &DAY_4,  &DAY_5,
                                  &DAY_6,  &DAY_7,  &DAY_8,  &DAY_9,  &DAY_10,
                                  &DAY_11, &DAY_12, &DAY_13, &DAY_14, &DAY_15,
                                  &DAY_16, &DAY_17, &DAY_18, &DAY_19, &DAY_20,
                                  &DAY_21, &DAY_22, &DAY_23, &DAY_24, &DAY_25};

char *run(int day) {
  if (--day >= 0 && day <= 24)
    return DAYS[day]();
  return "Unhandled Day";
}

int main(int argc, char *argv[]) {
  __clock_t begin = clock();
  if (argc == 2) {
    char *result = run(atoi(argv[1]));
    printf("%s\n", result);
    __clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nSeconds spent: %f\n", time_spent);
    return 0;
  }

  printf("%s\nAdvent of C\n\nUsage:\n  aoc [day]\n\n%s", BHRED, COLOR_RESET);
  return 1;
}
