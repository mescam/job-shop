#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "loader.h"
#include "orlib.h"
#include "taillard.h"

void print_program_info(char **argv) {
    printf("Job-Shop solving program\n");
    printf("Jakub Wozniak, Marcin Zaremba @ PUT\n");
    printf("Usage: %s type [filename [n]]\n", argv[0]);
    printf("Where:\n");
    printf("\ttype - o for orlib, t for taillard\n");
    printf("\tfilename - path to instance (stdin if not given)\n");
    printf("\tn - number of jobs to read from file\n");
}

int main(int argc, char **argv)
{
    format_reader type = NULL; //format of instance file
    instance *pi; //pointer to the instance
    char *p; //helper for strotol
    int c;
    char filename[255];
    char read_from_file = 0;
    int n = 0; //how many jobs we have to read, default 0 - all
    char measure_time = 0;

    while ((c = getopt (argc, argv, "t:f:mn:")) != -1) {
        switch (c) {
            case 't':
                if (strcmp("taillard", optarg) == 0)
                    type = taillard_loader;
                else if (strcmp("orlib", optarg) == 0)
                    type = orlib_loader;
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
        }
    }

    if (type == NULL) {
        print_program_info(argv);
        return 1;
    }

    if (read_from_file)
        pi = load(filename, type, n);
    else
        pi = type(stdin, 0);
    //debug print
    debug_print_as_orlib(pi);
    return 0;
}
