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

static void	process_create(t_var *var, int index)
{
	t_philo	*philo;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		philo = var->ph_array[index];
		while (var->n_meal == 0 || philo->n_eaten < var->n_meal)
		{
			if (get_time(var) - philo->last_meal > var->time_to_die)
			{
				put_action(var, philo, DIE);
				philo->pid = 0;
				exit(EXIT_SUCCESS);
			}
			eat(var, philo);
		}
		philo->pid = 0;
		exit(EXIT_SUCCESS);
	}
	else
		var->ph_array[index]->pid = pid;
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
	waitpid(-1, NULL, 0);
	i = -1;
	while(++i < var->n_philo)
	{
		if (var->ph_array[i]->pid != 0) 
			kill(var->ph_array[i]->pid, SIGKILL);
	}
	free_var(var);
	printf("\n");
	return (0);
}
