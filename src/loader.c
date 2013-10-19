#include <stdio.h>
#include <stdlib.h>
#include "loader.h"
/*
 * allocates memory for our structure and returns pointer
 */
instance *create_instance()
{
    return malloc(sizeof(instance));
}

/*
 * allocates memory for listing field
 * based on jobs and machines
 */
void alloc_listing(instance *pi)
{
    int i;
    pi->listing = malloc(sizeof(task*) * pi->jobs);
    for(i = 0; i < pi->machines; ++i)
        pi->listing[i] = malloc(sizeof(task) * pi->machines);
}

/*
 * reads instance file with given func and returns complete struct for
 * scheduling algorithm
 */
instance *load(const char* filename, format_reader reader, int n)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "Failed opening instance file - exiting.");
        exit(1);
    }
    instance *pi = reader(f, n);
    fclose(f);
    return pi;
}

void debug_print_as_orlib(instance *pi)
{
    printf("%d %d\n", pi->jobs, pi->machines);
    int i, j;
    for(i = 0; i < pi->jobs; i++) {
        for(j = 0; j < pi->machines; j++) {
            printf("%3d %3d ", pi->listing[i][j].machine, pi->listing[i][j].time);
        }
        printf("\n");
    }
}
