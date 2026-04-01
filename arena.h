/*
  Copyright (C) 2026  Daniel Maturano <carlosdanielmaturano@proton.me>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef _ARENA_H
#define _ARENA_H
#include <stdlib.h>
#include <string.h>

#define DEFAULT_ARENA_CAPACITY 1024 * 1024 // 1MB

typedef struct arena arena_t;

struct arena
{
    size_t capacity;
    size_t offset;
    arena_t* next; 
    char* data;
};

arena_t*
create_new_arena()
{
    char* data = malloc(sizeof(*data) * DEFAULT_ARENA_CAPACITY);
    if (NULL == data)
        return NULL;

    arena_t* new_arena = malloc(sizeof(*new_arena));

    if (NULL == new_arena)
        return NULL;
    
    new_arena->capacity = DEFAULT_ARENA_CAPACITY;
    new_arena->offset = 0;
    new_arena->data = data;
    new_arena->next = NULL;
    return new_arena;
}

void
free_arena(arena_t* arena)
{
    arena->capacity = 0;
    arena->offset = 0;
    free(arena->data);
    if (NULL != arena->next)
    {
        free_arena(arena->next);
        arena->next = NULL;
    }
}

void*
arena_try_alloc(arena_t* arena, size_t size)
{

    if (size > arena->capacity) // the block does not have enough capacity
        return NULL;
    
    if (arena->offset + size > arena->capacity) // not enough memory remaining on the block
    {
        if (NULL == arena->next)
        {
            arena->next = create_new_arena();
            return arena_try_alloc(arena->next, size);
        }
        return arena_try_alloc(arena->next, size);
    }
    
    void* ptr = &arena->data[arena->offset];
    arena->offset += size;
    return ptr;
}

void
reset_arena(arena_t* arena)
{
    memset(arena->data, 0, arena->capacity);
    arena->offset = 0;
    if (NULL != arena->next)
        reset_arena(arena->next);
}

#endif
