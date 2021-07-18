#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct		s_all
{
	int				count_ph;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_each_philo_to_eat;
	int 			any_died;
	int				total_eat;
	long int		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	ph_death;
	pthread_mutex_t	ph_print;
	t_philo 		*philo;

}					t_all;

typedef struct 		s_philo
{
	int 			id;
	pthread_t 		ph_thread;
	pthread_mutex_t eating;
	int				left_fork;
	int 			right_fork;
	int 			start;
	int 			end;
	int 			eat;
	long int 		last_eat;
	long int 		time_to_live;
	int 			finish;
	struct s_all	*main_info;
}					t_philo;

int	ft_atoi(const char *str);
int	ft_isdigit(int c);
int	ft_strlen(const char *str);
int print_error(char *str);
long int get_time_now();
void	ph_sleep(int t);

#endif