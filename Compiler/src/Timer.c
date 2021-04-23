#include "Timer.h"

#include <stdio.h>

#if 1 //defined(USE_TIMERS)

Timer timer_create() {
	Timer timer;
	timespec_get(&timer.beg_, TIME_UTC);
	return timer;
}

void timer_reset(Timer *timer){
    timespec_get(&timer->beg_, TIME_UTC);
}

double timer_elapsed(Timer *timer) {
	struct timespec curr;
	timespec_get(&curr, TIME_UTC);
    printf("%ld, %ld", curr.tv_sec, curr.tv_nsec);
	return (-(1000000000.0 * (double) timer->beg_.tv_sec + (double) timer->beg_.tv_nsec) + 
		(1000000000.0 * (double) curr.tv_sec + (double) curr.tv_nsec)) / 1000000000.0;
}

#endif /* USE_TIMERS */