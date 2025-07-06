/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:58:17 by guclemen          #+#    #+#             */
/*   Updated: 2025/07/06 19:26:16 by guclemen         ###   ########.fr       */
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

static int	take_forks(t_philo *philo)
{
	if (!philo->first_round_done && philo->id % 2 != 0)
		usleep(200);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_mutex_print(philo, "has taken a fork");
		if (philo->data->num_philos == 1)
		{
			usleep(philo->data->time_die * 1000);
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
		pthread_mutex_lock(philo->right_fork);
		ft_mutex_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		ft_mutex_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		ft_mutex_print(philo, "has taken a fork");
	}
	philo->first_round_done = 1;
	return (1);
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	eating(t_philo *philo)
{
	philo->last_meal_time = get_time();
	ft_mutex_print(philo, "is eating");
	philo->meals_eaten++;
	usleep(philo->data->time_eat * 1000);
}

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
	philo->last_meal_time = get_time();
	while (!ft_someone_died(philo))
	{
		if (!take_forks(philo) || (philo->data->has_meals_limit && philo->data->num_times_each_must_eat == philo->meals_eaten))
			break;
		eating(philo);
		drop_forks(philo);
		if (ft_someone_died(philo))
			break;
		ft_mutex_print(philo, "is sleeping");
		usleep(philo->data->time_sleep * 1000);
		ft_mutex_print(philo, "is thinking");
	}
	return (NULL);
}
