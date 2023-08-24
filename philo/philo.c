/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:08:24 by anda-cun          #+#    #+#             */
/*   Updated: 2023/08/24 18:18:12 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_dead_philo(t_philo *philo, int *all_ate)
{
	pthread_mutex_lock(&philo->m_start_eat_time);
	if ((get_cur_time(philo) - philo->start_eat_time) / 1000 > philo->data->ttd)
	{
		pthread_mutex_lock(&philo->data->m_deadguy);
		philo->data->deadguy = 1;
		pthread_mutex_unlock(&philo->data->m_deadguy);
		pthread_mutex_lock(&philo->data->m_time);
		if (*all_ate != philo->data->nb_of_philos)
			printf("\e[1;31m%ld\t%d died\n\033[0m", get_cur_time(philo) / 1000,
				philo->index + 1);
		pthread_mutex_unlock(&philo->data->m_time);
		pthread_mutex_unlock(&philo->m_start_eat_time);
		return (1);
	}
	pthread_mutex_unlock(&philo->m_start_eat_time);
	return (0);
}

void	check_all_ate(t_philo *philo, int *all_ate)
{
	pthread_mutex_lock(&philo->m_times_eaten);
	if (philo->times_eaten == philo->data->must_eat)
	{
		philo->times_eaten++;
		pthread_mutex_unlock(&philo->m_times_eaten);
		(*all_ate)++;
		if (*all_ate == philo->data->nb_of_philos)
		{
			pthread_mutex_lock(&philo->data->m_time);
			pthread_mutex_lock(&philo->data->m_deadguy);
			philo->data->deadguy = 1;
			pthread_mutex_unlock(&philo->data->m_deadguy);
			pthread_mutex_unlock(&philo->data->m_time);
		}
		return ;
	}
	pthread_mutex_unlock(&philo->m_times_eaten);
	return ;
}

void	philo_eat(t_philo *philo, int cur, int next)
{
	if (philo->index == 0)
	{
		cur = next;
		next = 0;
	}
	pthread_mutex_lock(&philo->data->m_fork[cur]);
	philo_print(philo, "has taken a fork", 37);
	if (philo->data->nb_of_philos == 1)
	{
		pthread_mutex_unlock(&philo->data->m_fork[cur]);
		usleep(philo->data->ttd * 1500);
		return ;
	}
	pthread_mutex_lock(&philo->data->m_fork[next]);
	pthread_mutex_lock(&philo->m_start_eat_time);
	philo->start_eat_time = get_cur_time(philo);
	pthread_mutex_unlock(&philo->m_start_eat_time);
	philo_print(philo, "is eating", 32);
	pthread_mutex_lock(&philo->m_times_eaten);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->m_times_eaten);
	usleep(philo->data->tte * 1000);
	philo_print(philo, "is sleeping", 34);
	pthread_mutex_unlock(&philo->data->m_fork[cur]);
	pthread_mutex_unlock(&philo->data->m_fork[next]);
}

void	*routine(void *philo_v)
{
	t_philo	*philo;
	int		deadguy;

	philo = (t_philo *)philo_v;
	deadguy = 0;
	philo_print(philo, "is thinking", 33);
	if (philo->index % 2 == 1)
		usleep(philo->data->tte * 1000);
	while (!deadguy)
	{
		usleep(100);
		philo_eat(philo, philo->index, (philo->index + 1)
			% philo->data->nb_of_philos);
		usleep(philo->data->tts * 1000);
		pthread_mutex_lock(&philo->data->m_deadguy);
		deadguy = philo->data->deadguy;
		pthread_mutex_unlock(&philo->data->m_deadguy);
		philo_print(philo, "is thinking", 33);
		if (philo->data->nb_of_philos % 2 != 0
			&& philo->data->tte > philo->data->tts)
			usleep((philo->data->tte * 2 - philo->data->tts) * 1000);
	}
	return (NULL);
}

int	init_philos(t_data *data, t_philo *philo, pthread_t *thread, int all_ate)
{
	int				i;
	struct timeval	tv;

	i = -1;
	gettimeofday(&tv, NULL);
	data->start_time = tv.tv_sec * 1000000 + tv.tv_usec;
	while (++i < data->nb_of_philos)
	{
		philo[i].data = data;
		philo[i].index = i;
		philo[i].times_eaten = 0;
		philo[i].start_eat_time = 0;
		pthread_mutex_init(&philo[i].m_start_eat_time, NULL);
		pthread_mutex_init(&philo[i].m_times_eaten, NULL);
		if (pthread_create(&thread[i], NULL, routine, (void *)&philo[i]) != 0)
			return (print_error("Error creating threads\n"));
	}
	i = 0;
	while (!check_dead_philo(&philo[i], &all_ate))
	{
		check_all_ate(&philo[i++], &all_ate);
		if (i == philo->data->nb_of_philos)
			i = 0;
	}
	return (0);
}
