#include "philo.h"

int ft_strdigit(char **argv, int i, int j)
{
    while (argv[i])
    {
        j = 0;
        while(argv[i][j])
        {
            if (!(ft_isdigit(argv[i][j])))
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

int check_negative(t_all *philo)
{
    if (philo->count_ph <= 0 || philo->time_to_die <= 0 || \
        philo->time_to_eat <= 0 || philo->time_to_sleep <= 0)
        return (0);
    return (1);
}

void init_mutex(t_all *all)
{
    pthread_mutex_init(&all->ph_death, NULL);
    pthread_mutex_init(&all->ph_print, NULL);
    all->any_died = 0;
    all->start_time = get_time_now();
}

int parse_and_check_argv(int argc, char **argv, t_all *all)
{
    if ((argc == 5 || argc == 6) && ft_strdigit(argv, 1, 0))
    {
        all->count_ph = ft_atoi(argv[1]);
        all->time_to_die = ft_atoi(argv[2]);
        all->time_to_eat = ft_atoi(argv[3]);
        all->time_to_sleep = ft_atoi(argv[4]);
        all->nbr_each_philo_to_eat = -1;
    }
    if (argc == 6)
    {
        all->nbr_each_philo_to_eat = ft_atoi(argv[5]);
        all->total_eat = all->nbr_each_philo_to_eat * all->count_ph;
    }
    if (!(check_negative(all)))
        return print_error("ERROR IN ARGUMENTS");
    all->forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * all->count_ph);
    all->philo = malloc(sizeof(t_philo) * all->count_ph);
    if (!all->forks || !all->philo)
        return print_error("ERROR MALLOC");
    init_mutex(all);
    return (1);
}

int print_error(char *str)
{
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
    return (0);
}

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
			printf("%lu %d is died\n", (get_time_now() - ph->main_info->start_time), ph->id);
			return (0);
		}
		else if (!ph->main_info->any_died && ph->end != -1 && \
			 ph->start >= ph->end)
			return (0);
		pthread_mutex_unlock(&ph->eating);
	}
	return (0);
}

void	ft_print(t_philo *p, char *str)
{
	if (!p->main_info->any_died && p->main_info->total_eat != 0)
	{
		pthread_mutex_lock(&p->main_info->ph_print);
		if (!p->main_info->any_died && p->main_info->total_eat != 0)
			printf("%lu %d %s\n", (get_time_now() - p->main_info->start_time), p->id, str);
		pthread_mutex_unlock(&p->main_info->ph_print);
	}
}

void	go_eat(t_philo *p)
{
	pthread_mutex_lock(&p->main_info->forks[p->right_fork]);
	ft_print(p, "has taken a fork");
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

void *each_activity(void *arg)
{
    t_philo *ph;
    pthread_t ch_dead;

    ph = (t_philo *)arg;
    ph->last_eat = get_time_now();
    if (pthread_create(&ch_dead, NULL, status, ph) != 0)
        return (0);
    pthread_detach(ch_dead);
    if (!(ph->id % 2) && ph->main_info->time_to_eat > 1)
        ph_sleep(ph->main_info->time_to_eat);
    while (!ph->main_info->any_died && (ph->end == -1 || ph->start < ph->end))
        go_eat(ph);
    return (0);

}

int start_activity(t_all *all, int i)
{
    void *ph;

    while (i < all->count_ph)
    {
        all->philo[i].main_info = all;
        all->philo[i].left_fork = i;
        all->philo[i].right_fork = (i + 1) % all->count_ph;
        all->philo[i].id = i + 1;
        all->philo[i].eat = 0;
        if (all->nbr_each_philo_to_eat > 0)
            all->philo[i].end = all->nbr_each_philo_to_eat;
        else
            all->philo[i].end = -1;
        all->philo[i].start = 0;
        pthread_mutex_init(&all->philo[i].eating, NULL);
        pthread_mutex_init(&all->forks[i], NULL);
        i++;
    }
    i = 0;
    while (i < all->count_ph)
    {
        ph = (void *)&all->philo[i];
        if (pthread_create(&all->philo[i].ph_thread, NULL, each_activity, ph) != 0)
            return (0);
        i++;
    }
    i = 0;
    while (i < all->count_ph)
    {
        pthread_join(all->philo[i].ph_thread, NULL);
        i++;
    }

    return (1);
}

int main(int argc, char **argv)
{
    t_all all;
    int i;

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