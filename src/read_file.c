#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

char *read_file(const char *path, size_t *size) {
  int fd = open(path, O_RDONLY | O_CLOEXEC);
  if (fd < 0)
    return NULL;

  struct stat st;
  if (fstat(fd, &st) < 0) {
    close(fd);
    return NULL;
  }
  *size = st.st_size;

  void *mapped_data = mmap(NULL, *size, PROT_READ, MAP_PRIVATE, fd, 0);
  close(fd);

  return (mapped_data == MAP_FAILED) ? NULL : mapped_data;
}
