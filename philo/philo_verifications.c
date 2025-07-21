/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_verifications.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:31:56 by guclemen          #+#    #+#             */
/*   Updated: 2025/07/21 10:33:05 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_someone_died(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(&philo->data->start_mutex);
	status = philo->data->someone_died;
	pthread_mutex_unlock(&philo->data->start_mutex);
	return (status);
}

int	am_i_dead(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(&philo->mutex_im_dead);
	status = philo->im_dead;
	pthread_mutex_unlock(&philo->mutex_im_dead);
	return (status);
}

int	am_i_satisfied(t_philo *philo)
{
	int	status;

	status = 0;
	if (!philo->data->has_meals_limit)
		return (status);
	pthread_mutex_lock(&philo->mutex_meals);
	if (philo->meals_eaten >= philo->data->num_times_must_eat)
	{
		philo->is_satisfied = 1;
		status = 1;
	}
	pthread_mutex_unlock(&philo->mutex_meals);
	return (status);
}
