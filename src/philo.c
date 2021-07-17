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

int check_negative(t_list *philo)
{
    if (philo->count_ph <= 0 || philo->time_to_die <= 0 || \
        philo->time_to_eat <= 0 || philo->time_to_sleep <= 0)
        return (0);
    return (1);
}

int parse_and_check_argv(int argc, char **argv, t_all *all)
{
    if ((argc == 5 || argc == 6) && ft_strdigit(argv, 1, 0))
    {
        all->arg.count_ph = ft_atoi(argv[1]);
        all->arg.time_to_die = ft_atoi(argv[2]);
        all->arg.time_to_eat = ft_atoi(argv[3]);
        all->arg.time_to_sleep = ft_atoi(argv[4]);
        all->arg.nbr_each_philo_to_eat = 0;
    }
    if (argc == 6)
        all->arg.nbr_each_philo_to_eat = ft_atoi(argv[5]);
    if (!(check_negative(&all->arg)))
        return (0);
    return (1);
}

int print_error(char *str)
{
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
    return (0);
}

void *monit_death(void *ph)
{
     t_philo *philos;

    philos = (t_philo *)ph;
    while(1)
    {
        if (get_time_now() - philos->last_eat > philos->main_info->time_to_die)
        {

        }
    }
}

void *activity(void *ph)
{
    t_philo *philos;
    pthread_t dead;

    philos = (t_philo *)ph;
    philos->last_eat = get_time_now();
    pthread_create(&dead, NULL, monit_death, ph);
    while (1)
    {

    }
    return (NULL);
}

int main(int argc, char **argv)
{
    t_all all;
    int i;
    pthread_t *philosohers;
    void *ph;

    i = 0;
    if (!(parse_and_check_argv(argc, argv, &all)))
        return (print_error("WRONG ARGUMENTS"));
    all.philo = (t_philo*)malloc(sizeof(t_philo) * all.arg.count_ph);
    philosohers = (pthread_t *)malloc(sizeof(pthread_t) * all.arg.count_ph);
    // if (!ph)
    //     return print_error("ERROR MALLOC");
    
    while (i < all.arg.count_ph)
    {
        ph = (void*)&all.philo[i];
        pthread_create(&philosohers[i], NULL, activity, ph);
        pthread_detach(philosohers[i]);
        i++;
    }
    return (0);
}