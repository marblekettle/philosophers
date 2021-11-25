/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 10:44:22 by bmans         #+#    #+#                 */
/*   Updated: 2021/11/25 14:19:06 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# ifndef UINT
#  define UINT unsigned int
# endif
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef enum e_state
{
	THINK,
	EAT,
	SLEEP,
	DEAD
}	t_state;

typedef struct s_philo
{
	pthread_t		philo_thr;
	UINT			id;
	t_state			state;
	unsigned char	fork;
	pthread_mutex_t	mutex;
	struct s_monit	*monit;
	UINT			eat;
}					t_philo;

typedef struct s_monit
{
	pthread_t	monit_thr;
	t_philo		**philo;
	UINT		n_philo;
	UINT		time;
	UINT		time_die;
	UINT		time_eat;
	UINT		time_sleep;
	UINT		total_eat;
}				t_monit;

void	*philosopher(void *philo);
void	*monitor(void *monit);

char	is_numeric(const char *str);
UINT	atoui(const char *str);

#endif
