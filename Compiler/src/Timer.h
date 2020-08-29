#ifndef TIMER_H_GUARD
#define TIMER_H_GUARD

//#include <chrono>
#include <time.h>

typedef struct Timer
{
	//typedef std::chrono::high_resolution_clock clock_;
	//typedef std::chrono::duration<double, std::ratio<1>> second_;
	//std::chrono::time_point<clock_> beg_;

	unsigned long long beg_;
} Timer;

Timer *timer_create() {
	//beg_ = time
	return NULL;
}
void reset() { }//beg_ = 0; }
double timer_elapsed(Timer *timer)
{
	return 1.0;
}

#endif /* TIMER_H_GUARD */