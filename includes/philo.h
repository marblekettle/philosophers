/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 10:44:22 by bmans         #+#    #+#                 */
/*   Updated: 2022/02/04 14:16:56 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# ifndef UINT
#  define UINT unsigned int
# endif
# ifndef HELP_MSG
#  define HELP_MSG "Format: ./philo number_of_philosophers \
					time_to_die time_to_eat time_to_sleep [number of \
					times_each_philosopher_must_eat]"
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
	struct s_reaper	*reaper;
	pthread_t		philo_thr;
	UINT			id;
	t_state			state;
	unsigned char	fork;
	unsigned char	*next_fork;
	pthread_mutex_t	mutex;
	pthread_mutex_t *next_mutex;
	struct s_monit	*monit;
	UINT			eat;
	UINT			last_eat;
}					t_philo;

typedef struct s_reaper
{
	t_philo			*philo;
	struct s_monit	*monit;
	pthread_t		reaper_thr;
	pthread_mutex_t	mutex;
	char			dead;
	UINT			time;
}					t_reaper;

typedef struct s_monit
{
	unsigned char	start;
	pthread_t		monit_thr;
	pthread_mutex_t	mutex;
	t_philo			**philo;
	t_reaper		**reaper;
	UINT			n_philo;
	UINT			time_die;
	UINT			time_eat;
	UINT			time_sleep;
	UINT			total_eat;
}				t_monit;

void	*philosopher(void *philo);
void	*monitor(void *monit);

char	is_numeric(const char *str);
UINT	atoui(const char *str);
void	help_message(void);

#endif
