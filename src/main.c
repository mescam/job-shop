#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "loader.h"
#include "orlib.h"
#include "taillard.h"
#include "scheduler.h"

#include "dummy_scheduler.h"
#include "greedy_scheduler.h"

void print_program_info(char **argv) {
    printf("Job-Shop solving program\n");
    printf("Jakub Wozniak, Marcin Zaremba @ PUT\n");
    printf("Usage: %s -t type -a algorithm [-f filename] [-n number] [-m]\n", argv[0]);
    printf("Where:\n");
    printf("\ttype - orlib or taillard\n");
    printf("\tfilename - path to instance (stdin if not given)\n");
    printf("\tnumber - number of jobs to read from file\n");
    printf("\t-m - add time of execution after results\n");
    printf("\talgorithm - scheduler algorithm: n/a\n");
}

int main(int argc, char **argv) {
    format_reader type = NULL; //format of instance file
    instance *pi; //pointer to the instance
    scheduler_func scheduler = NULL;
    int c, n = 0;
    char filename[255], read_from_file = 0, measure_time = 0, *p;
    double a_time;

    while ((c = getopt (argc, argv, "t:f:mn:a:")) != -1) {
        switch (c) {
            case 't':
                if (strcmp("taillard", optarg) == 0)
                    type = &taillard_loader;
                else if (strcmp("orlib", optarg) == 0)
                    type = &orlib_loader;
                else {
                    printf("Wrong format type\n");
                    return 1;
                }
                break;

            case 'f':
                read_from_file = 1;
                strcpy(filename, optarg);
                break;

            case 'n':
                n = strtol(optarg, &p, 10);
                break;

            case 'm':
                measure_time = 1;
                break;

            case 'a':
                if (strcmp("dummy", optarg) == 0) scheduler = &dummy_scheduler;
                else if(strcmp("greedy", optarg) == 0) scheduler = &greedy_scheduler;
                else {
                    printf("Wrong scheduler algorithm\n");
                    return 1;
                }
                break;
        }
    }

    if (type == NULL || scheduler == NULL) {
        print_program_info(argv);
        return 1;
    }

    if (read_from_file)
        pi = load(filename, type, n);
    else
        pi = type(stdin, 0);

    sched_result *res = solve(pi, scheduler, &a_time);

    print_result(res, pi);
    //free_result_struct(res, pi);
    //free_instance(pi);

    if(measure_time) printf("%f\n", a_time);
    return 0;
}
