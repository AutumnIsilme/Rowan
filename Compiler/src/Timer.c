#include "Timer.h"

Timer timer_create() {
	Timer t;
	gettimeofday(&t.beg_, NULL);
	return t;
}

void timer_reset(Timer *timer){
    gettimeofday(&timer->beg_, NULL);
}

double timer_elapsed(Timer *timer) {
	struct timeval curr;
	gettimeofday(&curr, NULL);
	return (-(1000000.0 * (double) timer->beg_.tv_sec + (double) timer->beg_.tv_usec) + 
		(1000000.0 * (double) curr.tv_sec + (double) curr.tv_usec)) / 1000000.0;
}