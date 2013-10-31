#include <stdio.h>
#include <stdlib.h>
#include "loader.h"
#include "orlib.h"

void orlib_read_tasks(FILE *f, task* arr, int machines, int job) {
    int i;
    for(i = 0; i < machines; i++) {
        fscanf(f, "%d %d", &(arr[i].machine), &(arr[i].time));
        arr[i].job_id = job;
    }
}

void orlib_read_jobs(FILE *f, instance *pi) {
    int i;
    for(i = 0; i < pi->jobs; i++) {
        orlib_read_tasks(f, pi->listing[i], pi->machines, i);
    }
}

instance *orlib_loader(FILE *f, int n) {
    instance *pi = create_instance();
    //read information about number of jobs and available machines
    fscanf(f, "%d %d", &(pi->jobs), &(pi->machines));
    if (n != 0 && pi->jobs > n)
        pi->jobs = n;
    alloc_listing(pi);
    orlib_read_jobs(f, pi);
    return pi;
}
