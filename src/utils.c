#include "philo.h"

long int	get_time_now(void)
{
	long int			time;
	struct timeval		cur_time;

	time = 0;
	if (gettimeofday(&cur_time, NULL) == -1)
		print_error("ERROR TO GET TIME");
	time = (cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000);
	return (time);
}

void	ph_sleep(int t)
{
	int	delta;
	int	start;

	start = get_time_now();
	delta = 0;
	while (delta < t)
	{
		delta = get_time_now() - start;
		usleep(100);
	}
}

int	print_error(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (0);
}

int	ft_strdigit(char **argv, int i, int j)
{
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(ft_isdigit(argv[i][j])))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_print(t_philo *p, char *str)
{
	if (!p->main_info->any_died && p->main_info->total_eat != 0)
	{
		pthread_mutex_lock(&p->main_info->ph_print);
		if (!p->main_info->any_died && p->main_info->total_eat != 0)
			printf("%lu %d %s\n", (get_time_now() - p->main_info->start_time), \
			p->id, str);
		pthread_mutex_unlock(&p->main_info->ph_print);
	}
}
