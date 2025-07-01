/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utilits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:58:17 by guclemen          #+#    #+#             */
/*   Updated: 2025/07/01 16:06:15 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->start_mutex);
	while (philo->data->start <= 0)
	{
		if (philo->data->start == -1)
			return (NULL);
		pthread_mutex_unlock(&philo->data->start_mutex);
		usleep(100);
		pthread_mutex_lock(&philo->data->start_mutex);
	}
	pthread_mutex_unlock(&philo->data->start_mutex);
	printf("Filosofo %d começou a rotina!\n", philo->id);
	return (NULL);
}

int	ft_create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, ft_routine, \
&data->philos[i]) != 0)
		{
			pthread_mutex_lock(&data->start_mutex);
			data->start = -1;
			pthread_mutex_unlock(&data->start_mutex);
			while (--i >= 0)
				pthread_join(data->philos[i].thread, NULL);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_error(char *msg, int ret, t_data *data)
{
	int	i;

	i = 0;
	if (msg)
	{
		ft_putstr_fd("Error :(\n", 2);
		ft_putstr_fd(msg, 2);
	}
	if (data)
	{
		if (data->forks)
		{
			while (i < data->num_philos)
			{
				pthread_mutex_destroy(&data->forks[i]);
				i++;
			}
			free(data->forks);
		}
		if (data->philos)
			free(data->philos);
		pthread_mutex_destroy(&data->start_mutex);
	}
	return (ret);
}
