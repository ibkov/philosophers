#include "philo.h"

void	*status(void *ptr)
{
	t_philo	*ph;

	ph = (t_philo *)ptr;
	while (!ph->main_info->any_died)
	{
		usleep(100);
		pthread_mutex_lock(&ph->eating);
		if (get_time_now() - ph->last_eat > (long)ph->main_info->time_to_die && \
			 !ph->main_info->any_died)
		{
			ph->main_info->any_died = 1;
			pthread_mutex_unlock(&ph->eating);
			pthread_mutex_lock(&ph->main_info->ph_death);
			printf("%lu %d is died\n", (get_time_now() - \
			ph->main_info->start_time), ph->id);
			return (0);
		}
		else if (!ph->main_info->any_died && ph->end != -1 && \
			 ph->start >= ph->end)
			return (0);
		pthread_mutex_unlock(&ph->eating);
	}
	return (0);
}

void	go_to_eat(t_philo *p)
{
	pthread_mutex_lock(&p->main_info->forks[p->right_fork]);
	ft_print(p, "has taken a fork");
	if (p->right_fork == p->left_fork)
	{
		pthread_mutex_unlock(&p->main_info->forks[p->left_fork]);
		ph_sleep(p->main_info->time_to_die + 5);
		return ;
	}
	pthread_mutex_lock(&p->main_info->forks[p->left_fork]);
	ft_print(p, "has taken a fork");
	pthread_mutex_lock(&p->eating);
	p->last_eat = get_time_now();
	ft_print(p, "is eating");
	p->start++;
	if (p->main_info->total_eat > 0)
		p->main_info->total_eat -= 1;
	ph_sleep(p->main_info->time_to_eat);
	pthread_mutex_unlock(&p->eating);
	pthread_mutex_unlock(&p->main_info->forks[p->right_fork]);
	pthread_mutex_unlock(&p->main_info->forks[p->left_fork]);
	ft_print(p, "is sleeping");
	ph_sleep(p->main_info->time_to_sleep);
	ft_print(p, "is thinking");
}

void	*each_activity(void *arg)
{
	t_philo		*ph;
	pthread_t	ch_dead;

	ph = (t_philo *)arg;
	ph->last_eat = get_time_now();
	if (pthread_create(&ch_dead, NULL, status, ph) != 0)
		return (0);
	pthread_detach(ch_dead);
	if ((ph->id % 2 == 0) && ph->main_info->time_to_eat > 1)
		ph_sleep(ph->main_info->time_to_eat);
	while (!ph->main_info->any_died && (ph->end == -1 || ph->start < ph->end))
		go_to_eat(ph);
	return (0);
}
