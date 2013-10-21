#include <stdio.h>
#include <stdlib.h>
#include "loader.h"
#include "orlib.h"
#include "taillard.h"

void print_program_info(const char *argv[]) {
    printf("Job-Shop solving program\n");
    printf("Jakub Wozniak, Marcin Zaremba @ PUT\n");
    printf("Usage: %s type [filename [n]]\n", argv[0]);
    printf("Where:\n");
    printf("\ttype - o for orlib, t for taillard\n");
    printf("\tfilename - path to instance (stdin if not given)\n");
    printf("\tn - number of jobs to read from file\n");
}

int main(int argc, const char *argv[])
{
    format_reader type; //format of instance file
    instance *pi; //pointer to the instance
    char *p; //helper for strotol

    if (argc < 2) { //if there are not enough arguments passed
        print_program_info(argv);
        return 1;
    }

    if (argv[1][0] != 'o' && argv[1][0] != 't') { //check for format
        printf("Wrong type.\n");
        return 1;
    }
    //choose our loader function
    type = (argv[1][0] == 'o') ? orlib_loader : taillard_loader;

    if (argc < 3) { //reading from stdin, calling loader func directly
        pi = type(stdin, 0);
    } else {
        int n = 0;
        if (argc == 4) //checking for n requirements
            n = strtol(argv[3], &p, 10);
        pi = load(argv[2], type, n); //loading our instance
    }

    //debug print
    debug_print_as_orlib(pi);
    return 0;
}
