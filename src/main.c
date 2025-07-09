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
#define BHRED "\033[1;91m"
#define COLOR_RESET "\033[0m"

// GTFO PULLING IN ENTIRE HEADER FILES FOR 1 OR 2 MACROS
extern int printf(const char *__restrict __format, ...);
extern int strcmp(const char *__s1, const char *__s2) __THROW __attribute_pure__
    __nonnull((1, 2));
extern int atoi(const char *__nptr) __THROW __attribute_pure__
    __nonnull((1)) __wur;

char *read_file(const char *path, size_t *size) {
  int fd = -1;
  void *mapped_data = NULL;
  register long syscall_ret __asm__("rax");

#define SYSCALL(number, arg1, arg2, arg3)                                      \
  __asm__ __volatile__("syscall"                                               \
                       : "=a"(syscall_ret)                                     \
                       : "a"(number), "D"(arg1), "S"(arg2), "d"(arg3)          \
                       : "rcx", "r11", "memory")

  // open the file
  SYSCALL(SYS_OPEN, path, O_RDONLY | O_CLOEXEC, 0);
  if ((fd = syscall_ret) < 0)
    return NULL; // if we fail return null

  // mem map file
  {
    register long mmap_flags __asm__("r10") = MAP_PRIVATE;
    register long mmap_fd __asm__("r8") = fd;
    register long mmap_offset __asm__("r9") = 0;
    __asm__ __volatile__("syscall"
                         : "=a"(mapped_data)
                         : "a"(SYS_MMAP), "D"(0), "S"(*size), "d"(PROT_READ),
                           "r"(mmap_flags), "r"(mmap_fd), "r"(mmap_offset)
                         : "rcx", "r11", "memory");
  }

  // close file descriptor
  SYSCALL(SYS_CLOSE, fd, 0, 0);
  return mapped_data;

#undef SYSCALL
}

char *DAY_1(void) {
  size_t size = 14000; // 1000 lines, 14 bytes each line

  return read_file("./input/a", &size);
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
const FunctionPointer DAYS[26] = {
    &DAY_1,  &DAY_1,  &DAY_2,  &DAY_3,  &DAY_4,  &DAY_5,  &DAY_6,
    &DAY_7,  &DAY_8,  &DAY_9,  &DAY_10, &DAY_11, &DAY_12, &DAY_13,
    &DAY_14, &DAY_15, &DAY_16, &DAY_17, &DAY_18, &DAY_19, &DAY_20,
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
