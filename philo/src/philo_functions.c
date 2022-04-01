/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:26:47 by jboumal           #+#    #+#             */
/*   Updated: 2022/03/31 18:26:49 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_var *var, t_philo *philo)
{
	if (var->n_philo % 2 == 1 && philo->index == 1)
	{
		while (!philo->right_dirty)
			usleep(50);
		pthread_mutex_lock(&philo->right_fork);
		philo->right_dirty = 0;
		put_action(var, philo, TAKE_FORK);
		while (*philo->left_dirty)
			usleep(50);
		pthread_mutex_lock(philo->left_fork);
		*philo->left_dirty = 1;
		put_action(var, philo, TAKE_FORK);
	}
	else if (philo->index % 2 == 1)
	{
		while (!philo->right_dirty)
			usleep(50);
		pthread_mutex_lock(&philo->right_fork);
		philo->right_dirty = 0;
		put_action(var, philo, TAKE_FORK);
		while (!*philo->left_dirty)
			usleep(50);
		pthread_mutex_lock(philo->left_fork);
		*philo->left_dirty = 0;
		put_action(var, philo, TAKE_FORK);
	}
	else
	{
		while (*philo->left_dirty)
			usleep(50);
		pthread_mutex_lock(philo->left_fork);
		*philo->left_dirty = 1;
		put_action(var, philo, TAKE_FORK);
		while (philo->right_dirty)
			usleep(50);
		pthread_mutex_lock(&philo->right_fork);
		philo->right_dirty = 1;
		put_action(var, philo, TAKE_FORK);
	}
	philo->n_eaten ++;
	philo->last_meal = get_time(var);
	put_action(var, philo, EAT);
	msleep(var->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	put_action(var, philo, SLEEP);
	msleep(var->time_to_sleep);
	put_action(var, philo, THINK);
}

int	starve(t_var *var, t_philo *philo)
{
	if (get_time(var) - philo->last_meal > var->time_to_die)
	{
		put_action(var, philo, DIE);
		return (1);
	}
	return (0);
}

void	wait_for_death(t_var *var)
{
	int	i;

	while (1)
	{		
		i = 0;
		while (i < var->n_philo)
		{
			if (var->n_meal > 0 && var->n_meal == var->ph_array[i]->n_eaten)
				return ;
			if (starve(var, var->ph_array[i]))
			{
				i = 0;
				while (i < var->n_philo)
				{
					var->ph_array[i]->dead = 1;
					i++;
				}
				return ;
			}
			i++;
		}
		usleep(1000);
	}
}
