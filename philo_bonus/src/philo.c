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

void	wait_all(t_var *var)
{
	int	i;
	int	status;

	i = 0;
	while (i < var->n_philo)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 42)
			kill_all(var);
		i++;
	}
}

void	kill_all(t_var *var)
{
	int	i;

	i = -1;
	while (++i < var->n_philo)
	{
		if (var->pid_array[i] != 0)
			kill(var->pid_array[i], SIGKILL);
	}
	free_var(var);
	exit(EXIT_SUCCESS);
}

void	put_action(t_var *var, t_philo *philo, int action)
{
	sem_wait(var->sem_stdout);
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
	if (action != DIE)
		sem_post(var->sem_stdout);
}

static void	pick_forks(t_var *var, t_philo *philo)
{
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
	put_action(var, philo, SLEEP);
	msleep(var->time_to_sleep);
	put_action(var, philo, THINK);
}
