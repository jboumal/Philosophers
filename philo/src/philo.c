#include "philo.h"

t_philo	*init_philo(t_var *var, t_list *list, int index)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
	{
		free(var);
		free(list);
		exit(EXIT_FAILURE);
	}
	philo->index = index;
	return (philo);
}

t_list	*init_list(t_var *var)
{
	t_list	*list;
	int		i;

	list = malloc(sizeof(t_list));
	if (!list)
	{
		free(var);
		exit(EXIT_FAILURE);
	}
	i = 1;
	while (i <= var->n_philo)
	{
		list->philo = init_philo(var, list, i);
	}
	return (list);
}

t_var	*init_var(int argc, char **argv)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		exit(EXIT_FAILURE);
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
	{
		free(var);
		exit(EXIT_FAILURE);
	}
	printf("done\n");
	printf("n_philo=%d\n", var->n_philo);
	return (var);
}

int	main(int argc, char **argv)
{
	t_var	*var;

	if (argc < 5 || argc > 6)
		return (0);
	var = init_var(argc, argv);
	return (0);
}
