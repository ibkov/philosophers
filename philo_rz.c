# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>



typedef s_philo
{
    int id;
    
}       t_philo;

int	ft_strlen(const char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int			minus_in_num;
	long long	number;

	minus_in_num = 0;
	number = 0;
	while ((*str >= 7 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
		minus_in_num = 1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		number = number * 10 + (*str - 48);
		str++;
	}
	if ((number > (number * 10)) && minus_in_num)
		return (0);
	if (number > (number * 10))
		return (-1);
	if (minus_in_num)
		return ((int)number * -1);
	return ((int)number);
}

int print_error(char *str)
{
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
    return (0);
}

long int get_time_now()
{
	long int			time;
	struct timeval		cur_time;

	time = 0;
	if (gettimeofday(&cur_time, NULL) == -1)
		print_error("ERROR TO GET TIME");
	time = (cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000);
	return (time);
}

int main(int argc, char **argv)
{
    pthread_t philosohers[5];

    for (int i = 0; i < 5; i++)
        pthread_create(philosohers[i], NULL, eating, )


    while (1)
    {
        printf("%ld\n", get_time_now());
        usleep(1000000);
    }
    return 0;
}
 

