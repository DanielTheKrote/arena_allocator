#ifndef _ARENA_H
#define _ARENA_H

#include <stdio.h>
#include <stdlib.h>   

#define DEFAULT_ARENA_CAPACITY 1024 * 1024 // 1MB

typedef struct
{
    size_t capacity;
    size_t offset;
    char** data;
} arena_t;

arena_t*
create_new_arena()
{
    char** data = malloc(sizeof(char) * DEFAULT_ARENA_CAPACITY);
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

#endif
