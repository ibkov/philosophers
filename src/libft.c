#include "philo.h"

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

int	check_negative(t_all *philo)
{
	if (philo->count_ph <= 0 || philo->time_to_die <= 0 || \
		philo->time_to_eat <= 0 || philo->time_to_sleep <= 0)
		return (0);
	return (1);
}
