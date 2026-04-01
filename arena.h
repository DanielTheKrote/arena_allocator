#ifndef _ARENA_H
#define _ARENA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DEFAULT_ARENA_CAPACITY 1024 * 1024 // 1MB

typedef struct
{
    size_t capacity;
    size_t offset;
    char* data;
} arena_t;

arena_t*
create_new_arena()
{
    char* data = malloc(sizeof(char) * DEFAULT_ARENA_CAPACITY);
    if (NULL == data)
    {
        return NULL;
    }
    arena_t* new_arena = malloc(sizeof(*new_arena));
    new_arena->capacity = DEFAULT_ARENA_CAPACITY;
    new_arena->offset = 0;
    new_arena->data = data;
    return new_arena;
}

void
free_arena(arena_t* arena)
{
    arena->capacity = 0;
    arena->offset = 0;
    free(arena->data);
}

void*
arena_try_alloc(arena_t* arena, size_t size)
{

    if (size > arena->capacity) // the block does not have enough capacity
        return NULL;
    
    if (arena->offset + size >= arena->capacity) // not enough memory remaining on the block
        return NULL;
    
    void* ptr = &arena->data[arena->offset];
    arena->offset += size;
    return ptr;
}

void
reset_arena(arena_t* arena)
{
    memset(arena->data, 0, arena->capacity);
    arena->offset = 0;
}

#endif
