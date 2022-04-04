/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <jboumal@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:34:13 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/02 15:34:16 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_action(t_var *var, t_philo *philo, int action)
{
	pthread_mutex_lock(&var->std_mutex);
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
	}
	else if (action == DIE)
	{
		printf("%d %d died\n", get_time(var), philo->index);
	}
	pthread_mutex_unlock(&var->std_mutex);
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
		if (time - time0 < ms * 1000 - 50)
			usleep(50);
		else
			usleep(ms / 1000 - (time - time0) / 1000000);
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

void	free_var(t_var *var)
{
	int	i;

	if (var)
	{
		pthread_mutex_destroy(&var->mutex);
		pthread_mutex_destroy(&var->std_mutex);
		if (var->ph_array)
		{
			i = 0;
			while (i < var->n_philo)
			{
				if (var->ph_array[i])
				{
					pthread_mutex_destroy(&var->ph_array[i]->right_fork);
					free(var->ph_array[i]);
				}
				i++;
			}
			free(var->ph_array);
		}
		free(var);
	}
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
