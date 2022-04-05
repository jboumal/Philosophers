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

void	msleep(int ms)
{
	t_time	t0;
	t_time	t;
	long	time0;
	long	time;

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

char	*ft_strdup(const char *src)
{
	char	*s;
	char	*dup;
	int		size;

	size = 0;
	s = (char *) src;
	while (*s++)
		size ++;
	dup = malloc((size + 1) * sizeof(char));
	if (!dup)
		return (0);
	s = dup;
	while (*src)
	{
		*s = *src;
		src ++;
		s ++;
	}
	*s = '\0';
	return (dup);
}

void	free_var(t_var *var)
{
	if (var)
	{
		if (var->forks_name)
		{
			sem_close(var->forks);
			sem_unlink(var->forks_name);
			free(var->forks_name);
		}
		if (var->sem_stdout_name)
		{
			sem_close(var->sem_stdout);
			sem_unlink(var->sem_stdout_name);
			free(var->sem_stdout_name);
		}
		if (var->pid_array)
			free(var->pid_array);
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
