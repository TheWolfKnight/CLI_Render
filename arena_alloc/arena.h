
#include <stdlib.c>

#ifndef _ARENA_ALLOC_DEF
#define _ARENA_ALLOC_DEF

typedef struct {
  size_t size;
  size_t curr_ptr;
  void* area;
} Arena;

Arena ARENA_alloc_arena(size_t size);
void* ARENA_get_slot(Arena *this, size_t);
void ARENA_free(Arena *this);

#endif // _ARENA_ALLOC_DEF

