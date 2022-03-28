#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_var
{
	int	n_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_meal;
}					t_var;

typedef struct s_philo
{
	int				index;
	int				last_meal;
	pthread_mutex_t	fork;
}					t_philo;

typedef struct s_list
{
	t_var	*prev;
	t_philo	*philo;
	t_var	*next;	
}					t_list;

int		ft_atoi(const char *str);

#endif
