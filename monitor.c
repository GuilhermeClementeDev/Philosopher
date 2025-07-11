/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:03:44 by guclemen          #+#    #+#             */
/*   Updated: 2025/07/11 16:28:18 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	are_philos_full(t_data *data)
{
	int	i;

	i = 0;
	if (data->has_meals_limit == 0)
		return (0);
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].mutex_meals);
		if (data->philos[i].meals_eaten < data->num_times_must_eat)
		{
			pthread_mutex_unlock(&data->philos[i].mutex_meals);
			return (0);
		}
		pthread_mutex_unlock(&data->philos[i].mutex_meals);
		i++;
	}
	return (1);
}

int	monitoring_deaths(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].mutex_im_dead);
		if (data->philos[i].im_dead)
		{
			pthread_mutex_lock(&data->start_mutex);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->start_mutex);
			pthread_mutex_unlock(&data->philos[i].mutex_im_dead);
			return (1);
		}
		pthread_mutex_unlock(&data->philos[i].mutex_im_dead);
		i++;
	}
	return (0);
}

void	*ft_monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (monitoring_deaths(data))
			break ;
		if (are_philos_full(data))
			break ;
		usleep(1000);
	}
	return (NULL);
}
