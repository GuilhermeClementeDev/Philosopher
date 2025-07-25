/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:58:17 by guclemen          #+#    #+#             */
/*   Updated: 2025/07/21 10:55:24 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static int	only_one_philo_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_im_dead);
	philo->im_dead = 1;
	pthread_mutex_unlock(&philo->mutex_im_dead);
	usleep(philo->data->time_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
	ft_mutex_print(philo, "died");
	return (0);
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
			only_one_philo_fork(philo);
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
	if (am_i_dead(philo) || ft_someone_died(philo))
	{
		drop_forks(philo);
		return (0);
	}
	return (1);
}

static void	eating(t_philo *philo)
{
	if (am_i_dead(philo) || ft_someone_died(philo))
		return ;
	ft_mutex_print(philo, "is eating");
	pthread_mutex_lock(&philo->mutex_meals);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->mutex_meals);
	ft_usleep(philo->data->time_eat, philo);
	if (am_i_dead(philo) || ft_someone_died(philo))
		return ;
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!wait_for_start(philo))
		return (NULL);
	pthread_mutex_lock(&philo->mutex_meals);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->mutex_meals);
	while (!ft_someone_died(philo) && \
!am_i_dead(philo) && !am_i_satisfied(philo))
	{
		if (!take_forks(philo))
			break ;
		eating(philo);
		drop_forks(philo);
		if (am_i_dead(philo) || ft_someone_died(philo))
			break ;
		ft_mutex_print(philo, "is sleeping");
		ft_usleep(philo->data->time_sleep, philo);
		if (am_i_dead(philo) || ft_someone_died(philo))
			break ;
		ft_mutex_print(philo, "is thinking");
	}
	return (NULL);
}
