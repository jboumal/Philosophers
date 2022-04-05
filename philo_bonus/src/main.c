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
	while (1)
	{
		if (var->n_meal != 0 && philo->n_eaten >= var->n_meal)
		{
			exit(EXIT_SUCCESS);
		}
		if (philo->last_meal != 0
			&& get_time(var) - philo->last_meal > var->time_to_die)
		{
			put_action(var, philo, DIE);
			exit(EXIT_SUCCESS);
		}
		usleep(1000);
	}
	return (NULL);
}

static void	process_create(t_var *var, int index)
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
		while (1)
		{
			eat(var, philo);
		}
	}
	else
		var->pid_array[index] = pid;
}

int	main(int argc, char **argv)
{
	t_var	*var;
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
		process_create(var, i);
	start(var);
	waitpid(-1, NULL, 0);
	i = -1;
	while (++i < var->n_philo)
	{
		if (var->pid_array[i] != 0)
			kill(var->pid_array[i], SIGKILL);
	}
	free_var(var);
	return (0);
}
