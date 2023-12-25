#include "mini_malloc.h"
#include <stdbool.h>
#include <stddef.h>
#include <string.h>


/**
 * Header struct that is used to keep track of the size of the block, whether
 * it is used or not, and a pointer to the next block.
 */
typedef struct Header {
  size_t size;
  bool used;
  struct Header *next;
} Header;

/**
 * Interface to the OS specific functions for requesting memory
 */
static void *sysalloc(size_t size);

/**
 * Interface to the OS specific functions for freeing memory
 */
static bool sysfree(void *ptr);

// OS Specific functions
#ifdef _WIN32
#include <windows.h>
static void *sysalloc(size_t size) {
  return VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
}

static bool sysfree(void *ptr) { return VirtualFree(ptr, 0, MEM_RELEASE); }

#elif __unix__
#include <sys/mman.h>
static void *sysalloc(size_t size) {
  return mmap(0, size, PROT_READ | PROT_WRITE | PROT_EXEC,
              MAP_ANON | MAP_PRIVATE, 0, 0);
}

static bool sysfree(void *ptr) {
  int res = munmap(ptr, 0);
  return res == 0;
}
#endif

static Header *start = NULL;

static Header *top = NULL;

static Header *find_free_block(size_t req_size) {
  Header *current = start;

  while (current != NULL) {
    if (current->size <= req_size && !current->used) {
      return current;
    }
    current = current->next;
  }

  // There are currently no created free blocks
  return NULL;
}

void *mini_malloc(size_t size) {
  Header *free_block = find_free_block(size);

  // First case, we found a free block!
  if (free_block != NULL) {
    free_block->used = true;
    return (char *)free_block + sizeof(Header);
  }

  // Second case, no free block found, we need to allocate a new one
  size_t total_size = sizeof(Header) + size;

  Header *new_block = (Header *)sysalloc(total_size);

  // We failed to allocate a new block
  if (new_block == NULL) {
    return NULL;
  }

  new_block->size = size;
  new_block->used = true;
  new_block->next = NULL;

  // If start is NULL, then this is the first block we are allocating
  if (start == NULL) {
    start = new_block;
  }

  // If top is not NULL, then we need to set the next pointer of the previous
  // block
  if (top != NULL) {
    top->next = new_block;
  }

  top = new_block;

  // Since new_block's type is Header, we need to add 1 to get the address of
  // the memory we want to return.
  return new_block + 1;
}

void *mini_calloc(size_t num, size_t size) {
  size_t total_size = num * size;

  void *ptr = mini_malloc(total_size);
  memset(ptr, 0, total_size);

  return ptr;
}

void mini_free(void *ptr) {

  // This is a valid case
  if (ptr == NULL) {
    return;
  }

  // We need to go back to the start of the block, which is 1 Header size before
  // the pointer
  Header *mem_start = (Header *)(ptr)-1;

  mem_start->used = false;
}
