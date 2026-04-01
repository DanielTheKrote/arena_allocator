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

    test_struct_t* t = arena_try_alloc(arena, sizeof(*t));
    t->x = 157171;
    t->y = 42069;


    char* buff = arena_try_alloc(arena, 1024 * 1024 * 2); // try to allocate 2MB
    if (NULL == buff)
    {
        printf("the arena does not have memory for the buff.\n");
    }

    printf("t.x = %d, t.y = %d\n", t->x, t->y);
    reset_arena(arena);
    printf("t.x = %d, t.y = %d\n", t->x, t->y);
    

    printf("offset: %ld, capacity: %ld, data[addr]: %p\n", arena->offset, arena->capacity, arena->data);
    free_arena(arena);
}
