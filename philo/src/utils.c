#include "philo.h"

int	ft_atoi(const char *str)
{
	long	nb;

	nb = 0;
	while (*str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		str ++;
	if (*str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9' || nb > 2147483647)
			return (-1);
		nb = nb * 10 + *str - '0';
		str ++;
	}
	return (nb);
}
