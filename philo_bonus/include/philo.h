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
# include <semaphore.h>
# include <signal.h>

typedef struct timeval	t_time;

enum
{
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
};

typedef struct s_var
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meal;
	t_time			t0;
	pid_t			*pid_array;
	sem_t			*forks;
	sem_t			*sem_stdout;
	char			*forks_name;
	char			*sem_stdout_name;
}					t_var;

typedef struct s_philo
{
	int				index;
	atomic_int		last_meal;
	atomic_int		n_eaten;
	pid_t			pid;
	pthread_t		pthread_id;
	t_var			*var;
}					t_philo;

/* init.c */
void	start(t_var *var);
t_philo	*init_philo(t_var *var, int index);
t_var	*init_var(int argc, char **argv);

/* utils.c */
void	msleep(int ms);
int		get_time(t_var *var);
char	*ft_strdup(const char *src);
void	free_var(t_var *var);
int		ft_atoi(const char *str);

/* philo.c */
void	wait_all(t_var *var);
void	kill_all(t_var *var);
void	put_action(t_var *var, t_philo *philo, int action);
void	die(t_var *var, t_philo *philo);
void	eat(t_var *var, t_philo *philo);

#endif
