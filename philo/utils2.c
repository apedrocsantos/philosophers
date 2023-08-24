/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:49:52 by anda-cun          #+#    #+#             */
/*   Updated: 2023/08/24 12:57:05 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->m_fork = malloc(sizeof(pthread_mutex_t) * data->nb_of_philos);
	if (!data)
		return (2);
	while (i < data->nb_of_philos)
		pthread_mutex_init(&data->m_fork[i++], NULL);
	pthread_mutex_init(&data->m_time, NULL);
	pthread_mutex_init(&data->m_deadguy, NULL);
	return (0);
}

int	init_data(t_data *data, int ac, char **av)
{
	data->ttd = (int)ft_atoi(av[2]);
	data->tte = (int)ft_atoi(av[3]);
	data->tts = (int)ft_atoi(av[4]);
	data->must_eat = -1;
	data->deadguy = 0;
	data->all_full = 0;
	if (ac == 6)
		data->must_eat = (int)ft_atoi(av[5]);
	if (data->nb_of_philos < 1 || data->ttd < 1 || data->tte < 1
		|| data->tts <= 0 || (ac == 6 && data->must_eat < 0))
		return (1);
	init_mutexes(data);
	return (0);
}
