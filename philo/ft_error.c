/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:23:35 by guclemen          #+#    #+#             */
/*   Updated: 2025/07/17 17:49:24 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int	ft_simple_error(char *msg, int ret)
{
	if (msg)
	{
		ft_putstr_fd("Error :(\n", 2);
		ft_putstr_fd(msg, 2);
	}
	return (ret);
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
		{
			i = 0;
			while (i < data->num_philos)
			{
				pthread_mutex_destroy(&data->philos[i].mutex_im_dead);
				pthread_mutex_destroy(&data->philos[i].mutex_meals);
				i++;
			}
			free(data->philos);
		}
		pthread_mutex_destroy(&data->start_mutex);
		pthread_mutex_destroy(&data->print_mutex);
	}
	return (ret);
}

