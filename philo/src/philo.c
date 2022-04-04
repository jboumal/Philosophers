/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <jboumal@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:30:36 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/02 16:30:39 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pick_right_fork(t_var *var, t_philo *philo, int tidy)
{
	while (!philo->dead && philo->right_dirty ^ !tidy)
		usleep(50);
	if (philo->dead)
		return ;
	pthread_mutex_lock(&philo->right_fork);
	philo->right_dirty = tidy;
	put_action(var, philo, TAKE_FORK);
}

static void	pick_left_fork(t_var *var, t_philo *philo, int tidy)
{
	while (!philo->dead && *philo->left_dirty ^ !tidy)
		usleep(50);
	if (philo->dead)
		return ;
	pthread_mutex_lock(philo->left_fork);
	*philo->left_dirty = tidy;
	put_action(var, philo, TAKE_FORK);
}

void	eat(t_var *var, t_philo *philo)
{
	if (var->n_philo % 2 == 1 && philo->index == 1)
	{
		pick_right_fork(var, philo, 0);
		pick_left_fork(var, philo, 1);
	}
	else if (philo->index % 2 == 1)
	{
		pick_right_fork(var, philo, 0);
		pick_left_fork(var, philo, 0);
	}
	else
	{
		pick_left_fork(var, philo, 1);
		pick_right_fork(var, philo, 1);
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
	int	i;

	if (get_time(var) - philo->last_meal > var->time_to_die)
	{
		i = 0;
		while (i < var->n_philo)
		{
			var->ph_array[i]->dead = 1;
			i++;
		}
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
				return ;
			i++;
		}
		usleep(50);
	}
}
