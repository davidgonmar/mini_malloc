#ifndef MINI_MALLOC_H_
#define MINI_MALLOC_H_

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Allocate a block of memory of size bytes.
 * @param size The size in bytes of the memory block to allocate.
 * @return A pointer to the allocated memory block.
 * @example Point *p = mini_malloc(sizeof(Point));
 */
void *mini_malloc(size_t size);

/**
 * @brief Free a block of memory previously allocated by mini_malloc.
 * @param ptr A pointer to the memory block to free.
 * @example mini_free(ptr);
 */
void mini_free(void *ptr);

#endif // MINI_MALLOC_H_