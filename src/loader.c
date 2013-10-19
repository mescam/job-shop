#include <stdio.h>
#include <stdlib.h>
#include "loader.h"
/*
 * allocates memory for our structure and returns pointer
 */
instance* create_instance()
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
 * reads instance file with given func and returns complete struct for scheduling
 * algorithm
 */
instance* load(char* filename, format_reader reader)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "Failed opening instance file - exiting.");
        exit(1);
    }
    instance *pi = reader(f);
    fclose(f);
    return pi;
}
