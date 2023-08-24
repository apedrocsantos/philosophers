/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:04:55 by anda-cun          #+#    #+#             */
/*   Updated: 2023/08/22 16:23:56 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				nb_of_philos;
	int				must_eat;
	int				deadguy;
	int				all_full;
	suseconds_t		ttd;
	suseconds_t		tte;
	suseconds_t		tts;
	suseconds_t		start_time;
	pthread_mutex_t	m_time;
	pthread_mutex_t	m_deadguy;
	pthread_mutex_t	*m_fork;
}					t_data;

typedef struct s_philo
{
	int				times_eaten;
	int				index;
	suseconds_t		start_eat_time;
	pthread_mutex_t	m_start_eat_time;
	pthread_mutex_t	m_times_eaten;
	t_data			*data;
}					t_philo;

/*************************main.c***********************/
int					init_philos(t_data *data, t_philo *philo, pthread_t *thread,
						int all_ate);
void				*routine(void *philo_v);
void				philo_eat(t_philo *philo, int cur, int next);

/*************************utils.c***********************/
long				ft_atoi(char *str);
void				exit_routine(t_data *data, t_philo *philo, pthread_t *fork);
int					print_error(char *msg);
suseconds_t			get_cur_time(t_philo *philo);
void				philo_print(t_philo *philo, char *str, int color);

/*************************utils2.c***********************/
int					init_data(t_data *data, int ac, char **av);
int					init_mutexes(t_data *data);
int					check_dead_philo(t_philo *philo, int *all_ate);
void				check_all_ate(t_philo *philo, int *all_ate);

#endif
