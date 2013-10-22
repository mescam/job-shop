#ifndef LOADER_H
#define LOADER_H
#include <stdio.h>

struct _task {
    int machine; //id of the machine
    int time; //duration
};

typedef struct _task task;

struct _instance {
    int jobs; //number of jobs
    int machines; //number of machines
    task **listing; //don't know how to describe it yet
};

typedef struct _instance instance;


typedef instance *(*format_reader)(FILE *f, int n);

instance *create_instance();
void alloc_listing(instance *pi);
void free_instance(instance *pi);
instance *load(const char* filename, format_reader reader, int n);
void debug_print_as_orlib(instance *pi);

#endif
