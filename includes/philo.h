/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 10:44:22 by bmans         #+#    #+#                 */
/*   Updated: 2022/02/11 11:37:57 by bmans         ########   odam.nl         */
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

typedef struct s_philo
{
	struct s_philo	*next;
	pthread_t		philo_thr;
	UINT			id;
	unsigned char	fork;
	pthread_mutex_t	mutex;
	pthread_mutex_t	f_mutex;
	struct s_monit	*monit;
	char			eat_fin;
	UINT			eat;
	UINT			last_eat;
}					t_philo;

typedef struct s_monit
{
	UINT			stop;
	pthread_mutex_t	mutex;
	t_philo			**philo;
	UINT			n_philo;
	UINT			time;
	UINT			time_die;
	UINT			time_eat;
	UINT			time_sleep;
	UINT			total_eat;
}				t_monit;

void	*philo_loop(void *philo);
void	monitor(t_monit *monit);
char	is_numeric(const char *str);
UINT	atoui(const char *str);
void	help_message(void);
char	error_message(char *msg);
void	time_message(t_philo *philo, char *msg, char priority);

#endif
