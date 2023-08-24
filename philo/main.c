/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:04:56 by anda-cun          #+#    #+#             */
/*   Updated: 2023/08/24 12:57:18 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_sim(t_data *data, t_philo *philo, pthread_t *thread)
{
	philo = malloc(sizeof(t_philo) * data->nb_of_philos);
	if (!philo)
	{
		free(data->m_fork);
		return (print_error("Error: Couldn't allocate memory\n"));
	}
	thread = malloc(sizeof(pthread_t) * data->nb_of_philos);
	if (!thread)
	{
		free(data->m_fork);
		free(philo);
		return (print_error("Error: Couldn't allocate memory\n"));
	}
	init_philos(data, philo, thread, 0);
	exit_routine(data, philo, thread);
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		*philo;
	pthread_t	*thread;

	philo = NULL;
	thread = NULL;
	if (ac != 5 && ac != 6)
		return (print_error("Error: Invalid values.\n"));
	data.nb_of_philos = (int)ft_atoi(av[1]);
	if (init_data(&data, ac, av))
		return (print_error("Error: Invalid values.\n"));
	if (ac == 6 && ft_atoi(av[5]) == 0)
	{
		free(data.m_fork);
		return (0);
	}
	if (init_sim(&data, philo, thread))
		return (1);
	return (0);
}
