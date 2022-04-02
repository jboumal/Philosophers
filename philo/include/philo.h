/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <jboumal@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:33:24 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/02 15:33:26 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdatomic.h>

typedef struct timeval	t_time;

enum
{
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
};

typedef struct s_philo
{
	int				index;
	atomic_int		last_meal;
	atomic_int		n_eaten;
	atomic_int		dead;
	atomic_int		right_dirty;
	atomic_int		*left_dirty;
	pthread_t		pthread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
}					t_philo;

typedef struct s_var
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meal;
	int				philo_id;
	t_time			t0;
	t_philo			**ph_array;
	pthread_mutex_t	mutex;
}					t_var;

/* init.c */
t_philo	*init_philo(int index);
int		init_ph_array(t_var *var);
t_var	*init_var(int argc, char **argv);

/* utils.c */
void	put_action(t_var *var, t_philo *philo, int action);
void	msleep(int ms);
int		get_time(t_var *var);
void	free_var(t_var *var);
int		ft_atoi(const char *str);

/* philo_functions.c */
void	die(t_var *var, t_philo *philo);
void	eat(t_var *var, t_philo *philo);
void	wait_for_death(t_var *var);

#endif
