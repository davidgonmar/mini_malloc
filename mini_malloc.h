#ifndef MINI_MALLOC_H_
#define MINI_MALLOC_H_

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Allocate a block of memory of size bytes.
 * @param size The size in bytes of the memory block to allocate.
 * @return A pointer to the allocated memory block.
 */
void *mini_malloc(size_t size);

/**
 * @brief Free a block of memory previously allocated by mini_malloc.
 * @param ptr A pointer to the memory block to free.
 */
void mini_free(void *ptr);

/**
 * @brief Allocate a block of memory for an array of n_elem elements of size
 * elem_size bytes each.
 * @param n_elem The number of elements in the array.
 * @param elem_size The size in bytes of each element.
 * @return A pointer to the allocated memory block.
 */
void *mini_calloc(size_t n_elem, size_t elem_size);

#endif // MINI_MALLOC_H_