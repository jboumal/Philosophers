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
	while(var->n_meal == 0 || philo->n_eaten < var->n_meal)
	{
		if (philo->dead)
			return (NULL);
		eat(var, philo);
	}
	return(NULL);
}

int	main(int argc, char **argv)
{
	t_var	*var;
	int		i;

	if (argc < 5 || argc > 6)
		return (-1);
	var = init_var(argc, argv);
	if (!var)
		return(-1);
	i = 0;
	while (i < var->n_philo)
	{
		pthread_create(&(var->ph_array[i]->pthread_id), NULL, philo_thread, var);
		i++;
	}
	wait_for_death(var);
	i = 0;
	while (i < var->n_philo)
	{
		pthread_join(var->ph_array[i]->pthread_id, NULL);
		i++;
	}
	//system("leaks philo");
	return (0);
}
