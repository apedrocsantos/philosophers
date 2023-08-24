/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:13:17 by anda-cun          #+#    #+#             */
/*   Updated: 2023/08/24 15:38:00 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_print(t_philo *philo, char *str, int color)
{
	pthread_mutex_lock(&philo->data->m_time);
	pthread_mutex_lock(&philo->data->m_deadguy);
	if (philo->data->deadguy == 1)
	{
		pthread_mutex_unlock(&philo->data->m_time);
		pthread_mutex_unlock(&philo->data->m_deadguy);
		return ;
	}
	printf("\e[1;%dm%ld\t%d %s\n\033[0m", color, get_cur_time(philo) / 1000,
		philo->index + 1, str);
	pthread_mutex_unlock(&philo->data->m_time);
	pthread_mutex_unlock(&philo->data->m_deadguy);
}

suseconds_t	get_cur_time(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000 + tv.tv_usec) - philo->data->start_time);
}

int	print_error(char *msg)
{
	int	len;

	len = 0;
	while (msg[len])
		len++;
	if (write(2, msg, len) == -1)
		printf("Error\n");
	return (1);
}

void	exit_routine(t_data *data, t_philo *philo, pthread_t *fork)
{
	int	i;

	i = -1;
	while (++i < philo->data->nb_of_philos)
	{
		if (pthread_join(fork[i], NULL))
			printf("Error joining thread\n");
	}
	i = -1;
	while (++i < philo->data->nb_of_philos)
	{
		pthread_mutex_destroy(&philo->data->m_fork[i]);
		pthread_mutex_destroy(&philo[i].m_start_eat_time);
		pthread_mutex_destroy(&philo[i].m_times_eaten);
	}
	pthread_mutex_destroy(&data->m_time);
	pthread_mutex_destroy(&data->m_deadguy);
	free(data->m_fork);
	free(philo);
	free(fork);
}

long	ft_atoi(char *str)
{
	int	result;

	result = 0;
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '+')
		str++;
	if (*str == '-')
		return (-1);
	while (*str >= '0' && *str <= '9')
		result = result * 10 + *str++ - '0';
	if (*str)
		return (-1);
	return (result);
}
