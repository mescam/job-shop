#include <stdio.h>
#include "loader.h"
#include "taillard.h"

#define TAILLARD_BUFF_MAX 16

// read one matrix
void taillard_read_lines(FILE *f, instance *pi) {
    char buff[TAILLARD_BUFF_MAX];
    int subject = 0;

    // read first line to determine what are we reading
    fscanf(f, "%s\n", buff);

    if(buff[0] == 'M')
        subject = 1;

    // iterate through whole matrix to fill detected parameter
    for(int i = 0; i < pi->jobs; i++) {
        for(int j = 0; j < pi->machines; j++) {
            fscanf(f, "%d ",
                    subject ? &(pi->listing[i][j].machine) : &(pi->listing[i][j].time));
        }
    }
}

instance *taillard_loader(FILE *f, int n) {
    instance *pi = create_instance();

    // grab first line essential info
    fscanf(f, "%d %d %*d %*d %*d %*d\n", &(pi->jobs), &(pi->machines));
    if (n != 0 && pi->jobs > n)
        pi->jobs = n;
    alloc_listing(pi);

    // read times
    taillard_read_lines(f, pi);

    // read machines
    taillard_read_lines(f, pi);

    return pi;
}
