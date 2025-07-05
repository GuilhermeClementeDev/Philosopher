/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:58:17 by guclemen          #+#    #+#             */
/*   Updated: 2025/07/05 16:47:37 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	philo->last_meal_time = ft_timestamp();
	while (!philo->data->someone_died)
	{
		if (!take_forks(philo))
			break;
		eating(philo);
		drop_forks(philo);
		if (philo->data->someone_died)
			break;
		ft_mutex_print(philo, "is sleeping");
		ft_usleep(philo->data->time_sleep);
		ft_mutex_print(philo, "is thinking");
	}
	return (NULL);
}
