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

  // Tests for mini_calloc

  Point *point3 = (Point *)mini_calloc(3, sizeof(Point));
  assert(point3 != NULL);
  assert(point3[0].x == 0);
  assert(point3[0].y == 0);
  assert(point3[1].x == 0);
  assert(point3[1].y == 0);
  assert(point3[2].x == 0);
  assert(point3[2].y == 0);
  mini_free(point3);

  Point *point4 = (Point *)mini_calloc(1, sizeof(Point));
  assert(point4 != NULL);
  assert(point4[0].x == 0);
  assert(point4[0].y == 0);

  // Tests for mini_realloc

  int *int_arr = (int *)mini_malloc(3 * sizeof(int));
  assert(int_arr != NULL);
  int_arr[0] = 10;
  int_arr[1] = 11;
  int_arr[2] = 12;

  int *new_int_arr = (int *)mini_realloc(int_arr, 5 * sizeof(int));
  assert(new_int_arr != NULL);
  assert(new_int_arr[0] == 10);
  assert(new_int_arr[1] == 11);
  assert(new_int_arr[2] == 12);

  new_int_arr[3] = 13;
  new_int_arr[4] = 14;

  assert(new_int_arr[3] == 13);
  assert(new_int_arr[4] == 14);

  printf("All tests passed!\n");

  return 0;
}
