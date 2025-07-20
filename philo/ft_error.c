/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:23:35 by guclemen          #+#    #+#             */
/*   Updated: 2025/07/20 11:53:43 by guclemen         ###   ########.fr       */
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

static void	free_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
}

static void	free_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->philos[i].mutex_im_dead);
		pthread_mutex_destroy(&data->philos[i].mutex_meals);
		i++;
	}
	free(data->philos);
}

int	ft_error(char *msg, int ret, t_data *data)
{
	ft_simple_error(msg, ret);
	if (data)
	{
		if (data->forks)
			free_forks(data);
		if (data->philos)
			free_philos(data);
		pthread_mutex_destroy(&data->start_mutex);
		pthread_mutex_destroy(&data->print_mutex);
	}
	return (ret);
}
