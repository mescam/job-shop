#include <stdlib.h>
#include <time.h>
#include "scheduler.h"
#include "loader.h"

sched_result *get_result_struct(instance *pi) {
    int i;
    sched_result *res = malloc(sizeof(sched_result));
    res->schedule = malloc(sizeof(int*) * pi->jobs);
    for (i = 0; i < pi->jobs; ++i) {
        res->schedule[i] = malloc(sizeof(int) * pi->machines);
    }
    return res;
}

void free_result_struct(sched_result *res, instance *pi) {
    int i;
    for (i = 0; i < pi->jobs; ++i) {
        free(res->schedule[i]);
    }
    free(res->schedule);
    free(res);
}

void print_result(sched_result *res, instance *pi) {
    printf("%d\n", res->scheduling_time);
    int i;
    for (i = 0; i < pi->jobs; i++) {
        int j;
        for (j = 0; j < pi->machines; j++)
            printf("%d ", res->schedule[i][j]);
        printf("\n");
    }
}

sched_result *solve(instance *pi, scheduler_func scheduler, double *mtime) {
    sched_result *result = get_result_struct(pi);
    struct timespec s1, s2;

    clock_gettime(CLOCK_REALTIME, &s1);
    scheduler(pi, result);
    clock_gettime(CLOCK_REALTIME, &s2);

    *mtime = (double) (s2.tv_sec - s1.tv_sec) + 1.e-9 * (s2.tv_nsec - s1.tv_nsec);
    return result;
}
