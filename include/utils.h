#include <time.h>
#include <sys/time.h>

#ifdef __MACH__
#define CLOCK_REALTIME 0
void clock_gettime(int, struct timespec *);
#endif

