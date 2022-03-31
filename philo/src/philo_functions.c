#include "philo.h"

int	starve(t_var *var, t_philo *philo)
{
	if (get_time(var) - philo->last_meal > var->time_to_die)
	{
		put_action(var, philo, DIE);
		return (1);
	}
	return (0);
}

void	eat(t_var *var, t_philo *philo)
{
	if (philo->index % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		put_action(var, philo, TAKE_FORK);
		pthread_mutex_lock(&philo->right_fork);
		put_action(var, philo, TAKE_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork);
		put_action(var, philo, TAKE_FORK);
		pthread_mutex_lock(philo->left_fork);
		put_action(var, philo, TAKE_FORK);
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
			{
				i = 0;
				while(i < var->n_philo)
				{
					var->ph_array[i]->dead = 1;
					i++;
				}
				return ;
			}
			i++;
		}
		usleep(1000);
	}
}
