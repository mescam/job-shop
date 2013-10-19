#include <stdio.h>
#include <stdlib.h>
#include "loader.h"
#include "orlib.h"

int main(int argc, const char *argv[])
{
    instance *pi = load(argv[1], &orlib_loader);
    debug_print_as_orlib(pi);
    free(pi);
    return 0;
}
