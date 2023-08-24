/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:13:17 by anda-cun          #+#    #+#             */
/*   Updated: 2023/08/24 13:16:07 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	philo_print(t_philo *philo, char *str, int color)
{
	sem_wait(philo->data->print);
	printf("\e[1;%dm%ld\t%d %s\n\033[0m", color, get_cur_time(philo),
		philo->index + 1, str);
	sem_post(philo->data->print);
}

long	get_cur_time(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - philo->data->start_time);
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

void	exit_routine(t_philo *philo)
{
	sem_close(philo->data->knife);
	sem_close(philo->data->get_forks);
	sem_close(philo->data->killall);
	sem_close(philo->data->print);
	sem_close(philo->data->all_ate);
	sem_unlink("/knife");
	sem_unlink("/get_forks");
	sem_unlink("/killall");
	sem_unlink("/print");
	sem_unlink("/all_ate");
	free(philo->data->pid);
	free(philo);
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
