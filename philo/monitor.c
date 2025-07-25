/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:03:44 by guclemen          #+#    #+#             */
/*   Updated: 2025/07/23 11:49:56 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	are_philos_full(t_data *data)
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

static int	handle_philo_death(t_data *data, t_philo *philo)
{
	pthread_mutex_unlock(&philo->mutex_meals);
	philo->im_dead = 1;
	pthread_mutex_unlock(&philo->mutex_im_dead);
	pthread_mutex_lock(&data->start_mutex);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->start_mutex);
	ft_mutex_print(philo, "died");
	return (1);
}

static int	monitoring_deaths(t_data *data)
{
	int			i;
	long long	now;

	i = 0;
	if (data->num_philos == 1)
		return (1);
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].mutex_meals);
		pthread_mutex_lock(&data->philos[i].mutex_im_dead);
		now = get_time();
		if (!data->philos[i].im_dead && !data->philos[i].is_satisfied
			&& now - data->philos[i].last_meal_time > data->time_die)
			return (handle_philo_death(data, &data->philos[i]));
		pthread_mutex_unlock(&data->philos[i].mutex_im_dead);
		pthread_mutex_unlock(&data->philos[i].mutex_meals);
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
