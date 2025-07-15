/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:58:17 by guclemen          #+#    #+#             */
/*   Updated: 2025/07/15 18:00:00 by guclemen         ###   ########.fr       */
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
	long long	now;
	int			status;

	now = get_time();
	pthread_mutex_lock(&philo->mutex_im_dead);
	if (philo->im_dead)
	{
		pthread_mutex_unlock(&philo->mutex_im_dead);
		return (1);
	}
	pthread_mutex_lock(&philo->mutex_meals);
	if (now - philo->last_meal_time > philo->data->time_die)
	{
		philo->im_dead = 1;
		status = 1;
	}
	else
		status = 0;
	pthread_mutex_unlock(&philo->mutex_meals);
	pthread_mutex_unlock(&philo->mutex_im_dead);
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
			pthread_mutex_lock(&philo->mutex_im_dead);
			ft_usleep(philo->data->time_die, philo);
			philo->im_dead = 1;
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(&philo->mutex_im_dead);
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
	ft_mutex_print(philo, "is eating");
	pthread_mutex_lock(&philo->mutex_meals);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->mutex_meals);
	ft_usleep(philo->data->time_eat, philo);
	pthread_mutex_lock(&philo->mutex_meals);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->mutex_meals);
}
int	am_i_satisfied(t_philo *philo)
{
	int	status;

	status = 0;
	if (!philo->data->has_meals_limit)
		return (status);
	pthread_mutex_lock(&philo->mutex_meals);
	if (philo->meals_eaten == philo->data->num_times_must_eat)
		{
			philo->is_satisfied = 1;
			status++;
		}
	pthread_mutex_unlock(&philo->mutex_meals);
	return (status);
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
	while (!ft_someone_died(philo) && !am_i_dead(philo) && !am_i_satisfied(philo))
	{
		if (!take_forks(philo))
			break;
		eating(philo);
		drop_forks(philo);
		ft_mutex_print(philo, "is sleeping");
		ft_usleep(philo->data->time_sleep, philo);
		ft_mutex_print(philo, "is thinking");
	}
	return (NULL);
}
