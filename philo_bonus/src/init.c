/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <jboumal@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:33:37 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/02 15:33:38 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->n_philo / 2)
	{
		sem_post(var->forks);
		i++;
	}
}

t_philo	*init_philo(t_var *var, int index)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->last_meal = 0;
	philo->n_eaten = 0;
	philo->index = index;
	philo->pid = 0;
	philo->var = var;
	return (philo);
}

static int	init_sem(t_var *var)
{
	var->forks_name = ft_strdup("sem_forks");
	var->sem_stdout_name = ft_strdup("sem_stdout");
	if (!var->forks_name || !var->sem_stdout_name)
		return (1);
	sem_unlink(var->forks_name);
	sem_unlink(var->sem_stdout_name);
	var->forks = sem_open(var->forks_name, O_CREAT, 0644, 0);
	var->sem_stdout = sem_open(var->sem_stdout_name, O_CREAT, 0644, 1);
	if (!var->forks)
		return (1);
	return (0);
}

t_var	*init_var(int argc, char **argv)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var->pid_array = NULL;
	var->forks_name = NULL;
	var->n_philo = ft_atoi(argv[1]);
	var->time_to_die = ft_atoi(argv[2]);
	var->time_to_eat = ft_atoi(argv[3]);
	var->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		var->n_meal = ft_atoi(argv[5]);
	else
		var->n_meal = 0;
	if (var->n_philo <= 0 || var->time_to_die < 0 || var->time_to_eat < 0
		|| var->time_to_sleep < 0 || var->n_meal < 0)
		return (NULL);
	gettimeofday(&var->t0, NULL);
	var->pid_array = malloc(sizeof(pid_t *) * var->n_philo);
	if (!var->pid_array)
		return (NULL);
	if (init_sem(var) != 0)
		return (NULL);
	return (var);
}
