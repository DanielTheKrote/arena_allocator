#include <stdio.h>
#include "arena.h"

typedef struct {
    int x;
    int y;
} test_struct_t;

int
main(int argc, char* argv[])
{
    arena_t* arena = create_new_arena();
    
    if (NULL == arena)
    {
        fprintf(stderr, "Error while creating a new arena.");
        exit(EXIT_FAILURE);
    }
    
    for (size_t j = 0; j < 10; j++)
        (void)arena_try_alloc(arena, 1024 * 512); // 0.5MB

    arena_t* curr = arena;
    while (curr != NULL)
    {
        printf("curr[addr]: %p\n" "offset: %ld\n" "1MB: %d\n" "0.5MB: %d\n", curr, curr->offset, 1024 * 1024, 1024 * 512);
        curr = curr->next;
    }

    
    reset_arena(arena);
    free_arena(arena);
}
