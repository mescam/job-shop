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

void greedy_feed_machines(instance *pi, int *iterators, task **machines,
                          int T, sched_result *result) {
    int i, j;
    for(i = 0; i < pi->machines; i++) { //for every machine
        if(machines[i] == NULL) { //if machine is in idle state
            //printf("Maszyna %d jest w stanie idle\n", i);
            for(j = 0; j < pi->jobs; j++) { //for every job
                //if jobs needs our idle-machine
                if(iterators[j] < pi->machines && pi->listing[j][iterators[j]].machine == i) {
                    //printf("Praca dla maszyny %d to [%d][%d]\n", i, j, iterators[j]);
                    machines[i] = &(pi->listing[j][iterators[j]]);
                    result->schedule[j][iterators[j]] = T;
                    break; //get ready!
                }
            }
        }
    }
}

int greedy_nearest_task_finish(instance *pi, task **machines) {
    int i, min;
    min = INT_MAX;
    for(i = 0; i < pi->machines; i++) {
        if(machines[i] != NULL && machines[i]->time < min)
            min = machines[i]->time;
    }
    //printf("Najblizsza chwila zakonczenia to +%d\n", min);
    return min;
}

void greedy_time_shift(task **machines, instance *pi, int timeshift) {
    int i;
    for(i = 0; i < pi->machines; i++) {
        if(machines[i] != NULL)
            machines[i]->time -= timeshift;
    }
}

void greedy_check_done_tasks(task **machines, instance *pi, int *iterators) {
    int i;
    for(i = 0; i < pi->machines; i++) {
        if (machines[i] != NULL && machines[i]->time == 0) {
            //printf("Maszyna %d skonczyla prace, zwalniam zasob\n", i);
            iterators[machines[i]->job_id]++;
            //printf("Iterator dla pracy %d zwiekszony do %d\n",
            //       machines[i]->job_id, iterators[machines[i]->job_id]);
            machines[i] = NULL;
        }
    }
}

void greedy_scheduler(instance *pi, sched_result *result) {
    //first, we need to keep machines states
    task **machines = malloc(sizeof(task*) * pi->machines);
    int i;
    for(i = 0; i < pi->machines; i++)
        machines[i] = NULL;
    int T = 0; //time for our simulation
    //task iterators for every job
    int *task_iterators = calloc(pi->jobs, sizeof(int));

    //initial machines states
    while(!greedy_are_we_ok(task_iterators, pi)) {
        greedy_feed_machines(pi, task_iterators, machines, T, result);
        int t = greedy_nearest_task_finish(pi, machines);
        T += t;
        //printf("Czas T=%d\n", T);
        greedy_time_shift(machines, pi, t);
        greedy_check_done_tasks(machines, pi, task_iterators);
    }
    result->scheduling_time = T;
    //cleaning
    free(machines);
    free(task_iterators);
}
