/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <jboumal@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:30:11 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/02 16:30:13 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_thread(void *arg)
{
	t_var	*var;
	t_philo	*philo;

	philo = (t_philo *) arg;
	var = philo->var;
	while (var->n_meal == 0 || philo->n_eaten < var->n_meal)
	{
		if (philo->last_meal != 0)
		{
			if (get_time(var) - philo->last_meal > var->time_to_die)
			{
				put_action(var, philo, DIE);
				exit(42);
			}
		}
		else if (get_time(var) > var->time_to_die)
		{
			put_action(var, philo, DIE);
			exit(42);
		}
		usleep(1000);
	}
	return (NULL);
}

static pid_t	process_create(t_var *var, int index)
{
	t_philo	*philo;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		philo = init_philo(var, index + 1);
		if (!philo)
		{
			free_var(var);
			exit(EXIT_FAILURE);
		}
		pthread_create(&(philo->pthread_id), NULL, death_thread, philo);
		while (var->n_meal == 0 || philo->n_eaten < var->n_meal)
			eat(var, philo);
		pthread_join(philo->pthread_id, NULL);
		return (pid);
	}
	else
		var->pid_array[index] = pid;
	return (pid);
}

int	main(int argc, char **argv)
{
	t_var	*var;
	pid_t	pid;
	int		i;

	if (argc < 5 || argc > 6)
		return (-1);
	var = init_var(argc, argv);
	if (!var)
	{
		free_var(var);
		return (-1);
	}
	i = -1;
	while (++i < var->n_philo)
	{
		pid = process_create(var, i);
		if (pid == 0)
			return (0);
	}
	start(var);
	wait_all(var);
	return (0);
}
