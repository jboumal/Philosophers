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

t_philo	*init_philo(int index)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->last_meal = 0;
	philo->n_eaten = 0;
	philo->index = index;
	philo->left_eat = 0;
	philo->pid = 0;
	return (philo);
}

int	init_ph_array(t_var *var)
{
	int	i;

	var->ph_array = malloc(sizeof(t_philo *) * var->n_philo);
	if (!var->ph_array)
		return (1);
	memset(var->ph_array, 0, sizeof(t_philo *) * var->n_philo);
	i = 0;
	while (i < var->n_philo)
	{
		var->ph_array[i] = init_philo(i + 1);
		if (!var->ph_array[i])
			return (1);
		i++;
	}
	return (0);
}

int	init_forks(t_var *var, char *name)
{
	int	i;

	var->forks_name = malloc(11 * sizeof(char));
	if (!var->forks_name)
		return (1);
	i = 0;
	while (i < 10)
	{
		var->forks_name[i] = *(name + i);
		i++;
	}
	var->forks_name[i] = 0;
	var->forks = sem_open(var->forks_name, O_CREAT, 0666, var->n_philo);
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
	var->ph_array = NULL;
	var->forks_name = NULL;
	var->n_philo = ft_atoi(argv[1]);
	var->time_to_die = ft_atoi(argv[2]);
	var->time_to_eat = ft_atoi(argv[3]);
	var->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		var->n_meal = ft_atoi(argv[5]);
	else
		var->n_meal = 0;
	if (var->n_philo < 0 || var->time_to_die < 0 || var->time_to_eat < 0
		|| var->time_to_sleep < 0 || var->n_meal < 0)
		return (NULL);
	gettimeofday(&var->t0, NULL);
	if (init_ph_array(var) != 0)
		return (NULL);
	if (init_forks(var, "sem_forks") != 0)
		return (NULL);
	return (var);
}
