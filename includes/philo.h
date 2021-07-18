#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct		s_info
{
	int				count_ph;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_each_philo_to_eat;
	int 			ph_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	ph_death;
	pthread_mutex_t	ph_print;
	pthread_mutex_t	ph_time;

}					t_info;

typedef struct 		s_philo
{
	int 			id;
	pthread_t 		th_id;
	pthread_t 		th_dead_id;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	long int 		time_begin;
	int 			time_to_eat;
	long int 		last_eat;
	unsigned int 	nb_of_eat;
	int 			finish;
	t_info		 	main_info;
}					t_philo;

typedef struct 	s_all
{
	t_philo 	*philo;
	t_info		info;
}				t_all;



int	ft_atoi(const char *str);
int	ft_isdigit(int c);
int	ft_strlen(const char *str);
int print_error(char *str);
long int get_time_now();
void	ph_sleep(int t);
void *activity(void *phi_arg);



#endif