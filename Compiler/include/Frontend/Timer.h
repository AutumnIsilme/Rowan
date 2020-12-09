#ifndef TIMER_H_GUARD
#define TIMER_H_GUARD

#include <sys/time.h>

typedef struct Timer
{
	struct timeval beg_;
} Timer;

Timer timer_create();
void timer_reset(Timer *timer);
double timer_elapsed(Timer *timer);

#endif /* TIMER_H_GUARD */