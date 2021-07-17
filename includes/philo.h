#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct		s_list
{
	int				count_ph;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_each_philo_to_eat;
	long int 		time_begin;

}					t_list;

typedef struct 		s_philo
{
	int 			id;
	pthread_t 		th_id;
	pthread_t 		th_dead_id;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	long int 		last_eat;
	unsigned int 	nb_of_eat;
	int 			finish;
	struct s_list 	*main_info;
}					t_philo;

typedef struct 	s_all
{
	t_philo 	*philo;
	t_list		arg;
}				t_all;



int	ft_atoi(const char *str);
int	ft_isdigit(int c);
int	ft_strlen(const char *str);
int print_error(char *str);
long int get_time_now();



#endif