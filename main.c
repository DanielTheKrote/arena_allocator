#include <stdio.h>
#include "arena.h"

int

main(int argc, char* argv[])
{
    arena_t* arena = create_new_arena();
    
    if (NULL == arena)
    {
        fprintf(stderr, "Error while creating a new arena.");
        exit(EXIT_FAILURE);
    }
    printf("offset: %ld, capacity: %ld, data[addr]: %p\n", arena->offset, arena->capacity, arena->data);
    free_arena(arena);
}
