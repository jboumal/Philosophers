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

void	*philo_thread(void *arg)
{
	t_var	*var;
	t_philo	*philo;

	var = (t_var *) arg;
	pthread_mutex_lock(&var->mutex);
	philo = var->ph_array[var->philo_id - 1];
	var->philo_id++;
	pthread_mutex_unlock(&var->mutex);
	while (var->n_meal == 0 || philo->n_eaten < var->n_meal)
	{
		if (philo->dead)
			return (NULL);
		eat(var, philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_var	*v;
	int		i;

	if (argc < 5 || argc > 6)
		return (-1);
	v = init_var(argc, argv);
	if (!v)
	{
		free_var(v);
		return (-1);
	}
	i = -1;
	while (++i < v->n_philo)
		pthread_create(&(v->ph_array[i]->pthread_id), NULL, philo_thread, v);
	wait_for_death(v);
	i = -1;
	while (++i < v->n_philo)
		pthread_join(v->ph_array[i]->pthread_id, NULL);
	free_var(v);
	return (0);
}
