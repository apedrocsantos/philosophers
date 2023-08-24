/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:04:55 by anda-cun          #+#    #+#             */
/*   Updated: 2023/08/24 12:44:06 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	int			nb_of_philos;
	int			must_eat;
	int			deadguy;
	long		ttd;
	long		tte;
	long		tts;
	pid_t		*pid;
	suseconds_t	start_time;
	sem_t		*knife;
	sem_t		*get_forks;
	sem_t		*killall;
	sem_t		*all_ate;
	sem_t		*print;
	pthread_t	thread;
}				t_data;

typedef struct s_philo
{
	int			times_eaten;
	int			index;
	long		start_eat_time;
	t_data		*data;
}				t_philo;

/*************************main.c***********************/
int				init_sim(t_philo *philo, t_data *data);
void			*check_all_ate(void *philo_v);
void			init_processes(t_philo *philo, int i, int pid);

/*************************init.c***********************/
int				init_data(t_data *data, int ac, char **av);
void			init_philos(t_philo *philo, t_data *data);

/*************************utils.c***********************/
long			ft_atoi(char *str);
void			exit_routine(t_philo *philo);
int				print_error(char *msg);
long			get_cur_time(t_philo *philo);
void			philo_print(t_philo *philo, char *str, int color);
long			sleep_time(t_philo *philo, long ttw);
#endif
