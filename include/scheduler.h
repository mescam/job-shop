#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "loader.h"

struct _sched_result {
    int scheduling_time;
    int **schedule;
};

typedef struct _sched_result sched_result;
void print_result(sched_result *res, instance *pi);
void free_result_struct(sched_result *res, instance *pi);
sched_result *get_result_struct(instance *pi);

typedef void (*scheduler_func)(instance *pi, sched_result *result);

sched_result *solve(instance *pi, scheduler_func scheduler, double *mtime);
#endif
