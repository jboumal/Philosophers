#include "philo.h"

void	put_action(t_var *var, t_philo *philo, int action)
{
	if (!philo->dead)
	{
		if (action == TAKE_FORK)
			printf("%d %d has taken a fork\n", get_time(var), philo->index);
		else if (action == EAT)
			printf("%d %d is eating\n", get_time(var), philo->index);
		else if (action == SLEEP)
			printf("%d %d is sleeping\n", get_time(var), philo->index);
		else if (action == THINK)
			printf("%d %d is thinking\n", get_time(var), philo->index);
		else if (action == DIE)
			printf("%d %d died\n", get_time(var), philo->index);
	}
}

void	msleep(int ms)
{
	t_time	t0;
	t_time	t;
	int		time0;
	int		time;

	gettimeofday(&t0, NULL);
	gettimeofday(&t, NULL);
	time0 = t0.tv_sec * 1000000 + t0.tv_usec;
	time = t.tv_sec * 1000000 + t.tv_usec;
	while (time - time0 < ms * 1000)
	{
		gettimeofday(&t, NULL);
		time = t.tv_sec * 1000000 + t.tv_usec;
		usleep(50);
	}
}

int	get_time(t_var *var)
{
	t_time	t;
	int		s;
	int		s0;
	int		ms;
	int		ms0;

	if (gettimeofday(&t, NULL) != 0)
		return (0);
	s = t.tv_sec * 1000;
	ms = t.tv_usec / 1000;
	s0 = var->t0.tv_sec * 1000;
	ms0 = var->t0.tv_usec / 1000;
	return (s - s0 + ms - ms0);
}

void	*free_var(t_var *var)
{
	int	i;

	if (var)
	{
		if (var->ph_array)
		{
			i = 0;
			while (i < var->n_philo)
			{
				if (var->ph_array[i])
					free(var->ph_array[i]);
			}
		}
		free(var);
	}
	return (NULL);
}

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
