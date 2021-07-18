#include "philo.h"

void put_msg(t_philo *phi, char *msg)
{
    pthread_mutex_lock(&phi->main_info.ph_print);
    if (phi->main_info.ph_died)
    {
        pthread_mutex_unlock(&phi->main_info.ph_print);
        return ;
    }
    printf("%ld %d %s", get_time_now() - phi->time_begin, phi->id, msg);
    pthread_mutex_unlock(&phi->main_info.ph_print);
}

void take_forks_eat(t_philo *phi)
{
    
}

void *check_each_death(void *phi_arg)
{
    t_philo *phi;

    phi = (t_philo*)phi_arg;
    pthread_mutex_lock(&phi->main_info.ph_time);
    while (get_time_now() - phi->last_eat <= phi->main_info.time_to_die)
    {
        pthread_mutex_unlock(&phi->main_info.ph_time);
        usleep(100);
        pthread_mutex_lock(&phi->main_info.ph_time);
    }
    pthread_mutex_unlock(&phi->main_info.ph_time);
    if (!phi->time_to_eat)
        return (NULL);
    pthread_mutex_lock(&phi->main_info.ph_death);
    if (phi->main_info.ph_died)
    {
        pthread_mutex_unlock(&phi->main_info.ph_death);
        return (NULL);
    }
    put_msg(phi, "is died\n");
    phi->main_info.ph_died = 1;
    pthread_mutex_unlock(&phi->main_info.ph_death);
    return (NULL);
}

void *activity(void *phi_arg)
{
    t_philo *phi;
    pthread_t death_th;

    phi = (t_philo*)phi_arg;
    phi->time_begin = get_time_now();
    phi->last_eat = phi->time_begin;
    pthread_create(&death_th, NULL, check_each_death, phi);
    while (phi->time_to_eat)
    {
        if (phi->main_info.ph_died)
            break ;
        take_forks_eat(phi);
        if (phi->time_to_eat > 0)
            phi->time_to_eat--;
        put_msg(phi, "is sleping\n");
        ph_sleep(phi->main_info.time_to_sleep);
        if (phi->main_info.ph_died)
            break ;
        put_msg(phi, "is thinking\n");
    }
    pthread_join(death_th, NULL);
    return (NULL);
}