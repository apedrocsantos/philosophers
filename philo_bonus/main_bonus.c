/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:00:49 by anda-cun          #+#    #+#             */
/*   Updated: 2023/08/24 13:29:42 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	init_sim(t_philo *philo, t_data *data)
{
	int				i;
	struct timeval	tv;

	init_philos(philo, data);
	if (pthread_create(&data->thread, NULL, check_all_ate, (void *)philo) != 0)
	{
		exit_routine(philo);
		print_error("Error creating thread\n");
		exit(1);
	}
	gettimeofday(&tv, NULL);
	data->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	init_processes(philo, -1, 0);
	sem_wait(data->killall);
	philo->data->deadguy = 1;
	sem_post(data->all_ate);
	pthread_join(data->thread, NULL);
	i = -1;
	while (++i < data->nb_of_philos)
		kill(data->pid[i], SIGKILL);
	exit_routine(philo);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	if (ac != 5 && ac != 6)
		return (print_error("Error: Invalid values.\n"));
	if (init_data(&data, ac, av))
		return (1);
	philo = malloc(sizeof(t_philo) * data.nb_of_philos);
	if (!philo)
		return (print_error("Couldn't allocate memory"));
	if (ac == 6 && ft_atoi(av[5]) == 0)
	{
		philo->data = &data;
		exit_routine(philo);
		return (0);
	}
	return (init_sim(philo, &data));
}
