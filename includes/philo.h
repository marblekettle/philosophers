/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 10:44:22 by bmans         #+#    #+#                 */
/*   Updated: 2022/02/07 14:04:30 by bmans         ########   odam.nl         */
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
	t_state			state;		//Written by philo, read by monit
	unsigned char	fork;		//Written by philo
	pthread_mutex_t	mutex;
	struct s_monit	*monit;
	UINT			eat;		//Written by philo
	UINT			last_eat;	//Written by philo
}					t_philo;

typedef struct s_monit
{
	unsigned char	start;
	char			any_dead;
	pthread_t		monit_thr;
	pthread_mutex_t	mutex;
	t_philo			**philo;
	UINT			n_philo;
	UINT			time;		//Written by monit, read by philo
	UINT			time_die;
	UINT			time_eat;
	UINT			time_sleep;
	UINT			total_eat;
}				t_monit;

void	*philosopher(void *philo);
void	*monitor(void *monit);

char	is_numeric(const char *str);
UINT	atoui(const char *str);

#endif
