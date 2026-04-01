#ifndef _ARENA_H
#define _ARENA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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
    char* data = malloc(sizeof(char) * DEFAULT_ARENA_CAPACITY);
    if (NULL == data)
    {
        return NULL;
    }
    arena_t* new_arena = malloc(sizeof(*new_arena));
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
