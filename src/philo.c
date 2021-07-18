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

int check_negative(t_info *philo)
{
    if (philo->count_ph <= 0 || philo->time_to_die <= 0 || \
        philo->time_to_eat <= 0 || philo->time_to_sleep <= 0)
        return (0);
    return (1);
}

void init_mutex(t_all *all, int i)
{
    while (i < all->info.count_ph)
        pthread_mutex_init(&all->info.forks[i++], NULL);
    // pthread_mutex_init(&all->info.ph_death, NULL);
    // pthread_mutex_init(&all->info.ph_print, NULL);
    // pthread_mutex_init(&all->info.ph_time, NULL);
}

int parse_and_check_argv(int argc, char **argv, t_all *all)
{
    if ((argc == 5 || argc == 6) && ft_strdigit(argv, 1, 0))
    {
        all->info.count_ph = ft_atoi(argv[1]);
        all->info.time_to_die = ft_atoi(argv[2]);
        all->info.time_to_eat = ft_atoi(argv[3]);
        all->info.time_to_sleep = ft_atoi(argv[4]);
        all->info.nbr_each_philo_to_eat = -1;
    }
    if (argc == 6)
        all->info.nbr_each_philo_to_eat = ft_atoi(argv[5]);
    if (!(check_negative(&all->info)))
        return print_error("ERROR IN ARGUMENTS");
    all->info.forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * all->info.count_ph);
    if (!all->info.forks)
        return print_error("ERROR MALLOC");
    init_mutex(all, 0);
    return (1);
}

int print_error(char *str)
{
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
    return (0);
}

static void		init_each_ph(t_all *all, t_philo *phi, int i)
{
	phi->id = i + 1;
	phi->time_to_eat = all->info.time_to_eat;
	phi->main_info = all->info;
}

int start_activity(t_all *all, int i)
{
    pthread_t   *philo_threads;
    t_philo     *phi;

    philo_threads = (pthread_t *)malloc(sizeof(pthread_t) * all->info.count_ph);
    phi = (t_philo*)malloc(sizeof(t_philo) * all->info.count_ph);
    if (!philo_threads || !phi)
        return print_error("ERROR MALLOC");
    while (i < all->info.count_ph)
    {
        init_each_ph(all, &phi[i], i);
        if (pthread_create(&philo_threads[i], NULL, activity, &phi[i]))
			return (1);
        i++;
    }
    while (i < all->info.count_ph)
    {
        if (pthread_join(philo_threads[i], NULL))
			return (1);
		if (pthread_mutex_destroy(&all->info.forks[i]))
			return (1);
        i++;
    }
    free(phi);
    free(philo_threads);
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
	pthread_mutex_destroy(&all.info.ph_death);
	pthread_mutex_destroy(&all.info.ph_print);
	pthread_mutex_destroy(&all.info.ph_time);
	free(all.info.forks);
    return (0);
}