/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:04:56 by anda-cun          #+#    #+#             */
/*   Updated: 2023/08/24 15:38:27 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*check_dead_philo(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	while (1)
	{
		if (philo->times_eaten == philo->data->must_eat)
		{
			philo->times_eaten++;
			sem_post(philo->data->all_ate);
		}
		if (get_cur_time(philo) - philo->start_eat_time > philo->data->ttd)
		{
			sem_wait(philo->data->print);
			printf("\e[1;31m%ld\t%d died\n\e[0m", get_cur_time(philo),
				philo->index + 1);
			sem_post(philo->data->killall);
			return (NULL);
		}
	}
	return (NULL);
}

void	*check_all_ate(void *philo_v)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)philo_v;
	while (1)
	{
		i = 0;
		while (i < philo->data->nb_of_philos)
		{
			sem_wait(philo->data->all_ate);
			if (philo->data->deadguy)
				return (NULL);
			i++;
		}
		sem_post(philo->data->killall);
		pthread_detach(philo->data->thread);
	}
	return (NULL);
}

void	do_things(t_philo *philo)
{
	usleep(100);
	sem_wait(philo->data->get_forks);
	sem_wait(philo->data->knife);
	philo_print(philo, "has taken a fork", 1);
	sem_wait(philo->data->knife);
	philo_print(philo, "has taken a fork", 1);
	philo->start_eat_time = get_cur_time(philo);
	philo_print(philo, "is eating", 32);
	philo->times_eaten++;
	usleep(philo->data->tte * 1000);
	philo_print(philo, "is sleeping", 34);
	sem_post(philo->data->knife);
	sem_post(philo->data->knife);
	sem_post(philo->data->get_forks);
	usleep(philo->data->tts * 1000);
	philo_print(philo, "is thinking", 33);
	if (philo->data->nb_of_philos % 2 != 0
		&& philo->data->tte >= philo->data->tts)
		usleep((philo->data->tte * 2 - philo->data->tts) * 1000);
}

int	philo_routine(t_philo *philo, pthread_t *thread)
{
	if (pthread_create(thread, NULL, check_dead_philo, (void *)philo) != 0)
	{
		print_error("Error creating thread in child process\n");
		sem_post(philo->data->killall);
		exit(1);
	}
	pthread_detach(*thread);
	while (1)
		do_things(philo);
}

void	init_processes(t_philo *philo, int i, int pid)
{
	pthread_t	thread;

	while (++i < philo->data->nb_of_philos)
	{
		pid = fork();
		if (pid == 0)
		{
			philo_print(&philo[i], "is thinking", 33);
			philo_routine(&philo[i], &thread);
		}
		else if (pid < 0)
		{
			if (i > 0)
			{
				while (--i >= 0)
					kill(philo->data->pid[i], SIGKILL);
				philo->data->deadguy = 1;
				sem_post(philo->data->all_ate);
				pthread_join(philo->data->thread, NULL);
			}
			exit_routine(philo);
			exit(print_error("Error creating child\n"));
		}
		philo->data->pid[i] = pid;
	}
}
