#include "philo.h"

long int get_time_now()
{
	long int			time;
	struct timeval		cur_time;

	time = 0;
	if (gettimeofday(&cur_time, NULL) == -1)
		print_error("ERROR TO GET TIME");
	time = (cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000);
	return (time);
}