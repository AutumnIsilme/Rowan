#ifndef _TIMER_H
#define _TIMER_H

#if 1 //defined(USE_TIMERS)

#include <time.h>

typedef struct Timer
{
	struct timespec beg_;
} Timer;

Timer timer_create();
void timer_reset(Timer *timer);
double timer_elapsed(Timer *timer);

#else

#define Timer unsigned int
#define timer_create(...) 0
#define timer_reset(...)
#define timer_elapsed(...) 0.0

#endif

#endif /* _TIMER_H */