#include "greedy_scheduler.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

//checks if every job is done
char greedy_are_we_ok(int *iterators, instance *pi) {
    int i;
    for(i = 0; i < pi->jobs; i++) {
        if(iterators[i] < pi->machines)
            return 0;
    }
    return 1;
}

int greedy_feed_machines(instance *pi, int *iterators, task **machines,
                          long long int T, sched_result *result) {
    int i, j, min = INT_MAX;
    for(i = 0; i < pi->machines; i++) { //for every machine
        if(machines[i] == NULL) { //if machine is in idle state
            for(j = 0; j < pi->jobs; j++) { //for every job
                //if jobs needs our idle-machine
                if(iterators[j] < pi->machines && pi->listing[j][iterators[j]].machine == i) {
                    machines[i] = &(pi->listing[j][iterators[j]]);
                    result->schedule[j][iterators[j]] = T;
                    if(machines[i]->time < min)
                        min = machines[i]->time;
                    break; //get ready!
                }
            }
        } else {
            if(machines[i]->time < min)
                min = machines[i]->time;
        }
    }
    return min;
}

void greedy_time_shift(task **machines, instance *pi, int timeshift, int *iterators) {
    int i;
    for(i = 0; i < pi->machines; i++) {
        if(machines[i] != NULL) {
            machines[i]->time -= timeshift;
            if(machines[i]->time == 0) {
                iterators[machines[i]->job_id]++;
                machines[i] = NULL;
            }
        }
    }
}


void greedy_scheduler(instance *pi, sched_result *result) {
    //first, we need to keep machines states
    task **machines = malloc(sizeof(task*) * pi->machines);
    int i;
    for(i = 0; i < pi->machines; i++)
        machines[i] = NULL;
    long long int T = 0; //time for our simulation
    //task iterators for every job
    int *task_iterators = calloc(pi->jobs, sizeof(int));

    //initial machines states
    while(!greedy_are_we_ok(task_iterators, pi)) {
        int t = greedy_feed_machines(pi, task_iterators, machines, T, result);
        T += t;
        greedy_time_shift(machines, pi, t, task_iterators);
    }
    result->scheduling_time = T;
    //cleaning
    free(machines);
    free(task_iterators);
}
