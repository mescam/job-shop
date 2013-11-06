#include <stdio.h>
#include "loader.h"
#include "taillard.h"

#define TAILLARD_BUFF_MAX 256

// read one matrix
void taillard_read_lines(FILE *f, instance *pi, int initial_n, int n) {
    char buff[TAILLARD_BUFF_MAX];
    int subject = 0;

    // if n not specified, read all
    if(n == 0)
        n = pi->jobs;

    // read first line to determine what are we reading
    fscanf(f, "%s\n", buff);

    if(buff[0] == 'M')
        subject = 1;

    // iterate through whole matrix to fill detected parameter
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < pi->machines; j++) {
            fscanf(f, "%d ",
                    subject ? &(pi->listing[i][j].machine) : &(pi->listing[i][j].time));
        }
    }

    // read this bunch of unused crap
    int spare_reading = (initial_n - n) * pi->machines;

    for(int i = 0; i < spare_reading; i++)
        fscanf(f, "%*d ");
}

void taillard_fill_job_id(instance *pi) {
    int i, j;
    for(i = 0; i < pi->jobs; i++)
        for(j = 0; j < pi->machines; j++) {
            pi->listing[i][j].job_id = i;
            pi->listing[i][j].machine -= 1; //we need machines counted from 0
        }
}

instance *taillard_loader(FILE *f, int n) {
    instance *pi = create_instance();

    // grab first line essential info
    fscanf(f, "%d %d %*d %*d %*d %*d\n", &(pi->jobs), &(pi->machines));

    // save initial number of jobs
    int initial_jobs = pi->jobs;

    if (n != 0 && pi->jobs > n)
        pi->jobs = n;
    alloc_listing(pi);

    // read times
    taillard_read_lines(f, pi, initial_jobs, n);

    // read machines
    taillard_read_lines(f, pi, initial_jobs, n);

    //fill job_id
    taillard_fill_job_id(pi);

    return pi;
}
