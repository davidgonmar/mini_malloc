#include "mini_malloc.h"
#include <assert.h>
#include <stdio.h>

typedef struct Point {
  int x;
  int y;
} Point;

int main() {
  int *p = (int *)mini_malloc(sizeof(int));

  *p = 10;

  assert(p != NULL);
  assert(*p == 10);

  Point *point = (Point *)mini_malloc(sizeof(Point));
  assert(point != NULL);
  point->x = 10;
  point->y = 11;

  assert(point->x == 10);
  assert(point->y == 11);

  mini_free(point);

  Point *point2 = (Point *)mini_malloc(sizeof(Point));
  assert(point2 != NULL);
  point2->x = 20;
  point2->y = 21;

  // Test that it the new block's address is the same as the old one
  assert(point2 == point);

  assert(point2->x == 20);
  assert(point2->y == 21);

  printf("All tests passed!\n");
  return 0;
}
