/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:03:44 by guclemen          #+#    #+#             */
/*   Updated: 2025/07/10 23:04:53 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	int		i;

	while (1)
	{
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
				break ;
			}
			pthread_mutex_unlock(&data->philos[i].mutex_im_dead);
			i++;
		}
		if (check_all_philos_full(data))
				break ;
		usleep(1000);
	}
}
