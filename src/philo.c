#include "philo.h"

int	init_mutex(t_all *all)
{
	all->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* all->count_ph);
	all->philo = malloc(sizeof(t_philo) * all->count_ph);
	if (!all->forks || !all->philo)
		return (print_error("ERROR MALLOC"));
	pthread_mutex_init(&all->ph_death, NULL);
	pthread_mutex_init(&all->ph_print, NULL);
	all->any_died = 0;
	all->start_time = get_time_now();
	return (1);
}

int	parse_and_check_argv(int argc, char **argv, t_all *all)
{
	if ((argc == 5 || argc == 6) && ft_strdigit(argv, 1, 0))
	{
		all->count_ph = ft_atoi(argv[1]);
		all->time_to_die = ft_atoi(argv[2]);
		all->time_to_eat = ft_atoi(argv[3]);
		all->time_to_sleep = ft_atoi(argv[4]);
		all->nbr_each_philo_to_eat = -1;
	}
	else
		return (print_error("ERROR IN ARGUMENTS"));
	if (argc == 6)
	{
		all->nbr_each_philo_to_eat = ft_atoi(argv[5]);
		if (all->nbr_each_philo_to_eat > 0)
			all->total_eat = all->nbr_each_philo_to_eat * all->count_ph;
		else
			all->total_eat = -1;
	}
	if (!(check_negative(all)))
		return (print_error("ERROR IN ARGUMENTS"));
	if (!(init_mutex(all)))
		return (0);
	return (1);
}

void	init_phi(t_all *all, int *i)
{
	all->philo[*i].main_info = all;
	all->philo[*i].left_fork = *i;
	all->philo[*i].right_fork = (*i + 1) % all->count_ph;
	all->philo[*i].id = *i + 1;
	all->philo[*i].eat = 0;
	if (all->nbr_each_philo_to_eat > 0)
		all->philo[*i].end = all->nbr_each_philo_to_eat;
	else
		all->philo[*i].end = -1;
	all->philo[*i].start = 0;
	pthread_mutex_init(&all->philo[*i].eating, NULL);
	pthread_mutex_init(&all->forks[*i], NULL);
	(*i)++;
}

int	start_activity(t_all *all, int i)
{
	void	*ph;

	while (i < all->count_ph)
		init_phi(all, &i);
	i = 0;
	while (i < all->count_ph)
	{
		ph = (void *)&all->philo[i];
		if (pthread_create(&all->philo[i].ph_thread, \
		NULL, each_activity, ph) != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < all->count_ph)
		pthread_join(all->philo[i++].ph_thread, NULL);
	return (1);
}

int	main(int argc, char **argv)
{
	t_all	all;
	int		i;

	i = 0;
	if (!(parse_and_check_argv(argc, argv, &all)))
		return (1);
	start_activity(&all, 0);
	pthread_mutex_destroy(all.forks);
	pthread_mutex_destroy(&all.ph_print);
	pthread_mutex_destroy(&all.ph_death);
	free(all.forks);
	free(all.philo);
	return (0);
}
