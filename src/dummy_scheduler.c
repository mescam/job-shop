#include "dummy_scheduler.h"

void dummy_scheduler(instance *pi, sched_result *result) {
    result->scheduling_time = 0;
    int i, j;
    for (i = 0; i < pi->jobs; i++)
        for (j = 0; j < pi->machines; j++)
            result->schedule[i][j] = 0;
}
