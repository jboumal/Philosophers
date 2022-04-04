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

static void	pick_forks(t_var *var, t_philo *philo)
{
	sem_wait(var->forks);
	sem_wait(var->forks);
	put_action(var, philo, TAKE_FORK);
	put_action(var, philo, TAKE_FORK);
}

void	eat(t_var *var, t_philo *philo)
{
	pick_forks(var, philo);
	philo->n_eaten ++;
	philo->last_meal = get_time(var);
	put_action(var, philo, EAT);
	msleep(var->time_to_eat);
	sem_post(var->forks);
	sem_post(var->forks);
	put_action(var, philo, SLEEP);
	msleep(var->time_to_sleep);
	put_action(var, philo, THINK);
}
