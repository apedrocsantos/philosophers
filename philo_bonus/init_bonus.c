/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:49:52 by anda-cun          #+#    #+#             */
/*   Updated: 2023/08/24 15:40:29 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	init_sems(t_data *data)
{
	sem_unlink("/knife");
	sem_unlink("/killall");
	sem_unlink("/print");
	sem_unlink("/all_ate");
	sem_unlink("/get_forks");
	data->knife = sem_open("/knife", O_CREAT, O_RDWR, data->nb_of_philos);
	if (data->knife == SEM_FAILED)
		return (print_error("Error knife"));
	data->get_forks = sem_open("/get_forks", O_CREAT, O_RDWR, data->nb_of_philos
			/ 2);
	if (data->get_forks == SEM_FAILED)
		return (print_error("Error get_forks"));
	data->killall = sem_open("/killall", O_CREAT, O_RDWR, 0);
	if (data->killall == SEM_FAILED)
		return (print_error("error killall\n"));
	data->print = sem_open("/print", O_CREAT, O_RDWR, 1);
	if (data->print == SEM_FAILED)
		return (print_error("error print\n"));
	data->all_ate = sem_open("/all_ate", O_CREAT, O_RDWR, 0);
	if (data->all_ate == SEM_FAILED)
		return (print_error("error all_ate\n"));
	return (0);
}

void	init_philos(t_philo *philo, t_data *data)
{
	int	i;
	int	size;

	i = 0;
	size = data->nb_of_philos;
	while (i < size)
	{
		philo[i].data = data;
		philo[i].index = i;
		philo[i].times_eaten = 0;
		philo[i++].start_eat_time = 0;
	}
}

int	init_data(t_data *data, int ac, char **av)
{
	data->nb_of_philos = (int)ft_atoi(av[1]);
	data->ttd = (int)ft_atoi(av[2]);
	data->tte = (int)ft_atoi(av[3]);
	data->tts = (int)ft_atoi(av[4]);
	data->deadguy = 0;
	data->must_eat = -1;
	data->pid = malloc(sizeof(pid_t) * data->nb_of_philos);
	if (!data->pid)
		return (print_error("Error alocating memory\n"));
	if (ac == 6)
		data->must_eat = (int)ft_atoi(av[5]);
	if (data->nb_of_philos < 1 || data->ttd < 1 || data->tte < 1
		|| data->tts <= 0 || (ac == 6 && data->must_eat < 0))
		return (print_error("Error: Invalid values.\n"));
	return (init_sems(data));
}
