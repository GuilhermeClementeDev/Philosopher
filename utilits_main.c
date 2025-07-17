/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:01:45 by guclemen          #+#    #+#             */
/*   Updated: 2025/07/17 15:53:20 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isallnum(int argc, char **argv)
{
	int	i;
	int	size;

	size = argc;
	while (size > 1)
	{
		i = 0;
		if (argv[size - 1][i] == '+')
			i++;
		while (argv[size - 1][i])
		{
			if (!ft_isdigit(argv[size - 1][i]))
				return (0);
			i++;
		}
		size--;
	}
	return (1);
}

void	build_data(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->has_meals_limit = 1;
		data->num_times_must_eat = ft_atoi(argv[5]);
	}
	else
	{
		data->has_meals_limit = 0;
		data->num_times_must_eat = -1;
	}
	data->someone_died = 0;
	data->start = 0;
	pthread_mutex_init(&data->start_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
}

int	ft_create_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_build_philos_data(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (0);
	while (i < data->num_philos)
	{
		data->philos[i].id = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].data = data;
		data->philos[i].first_round_done = 0;
		data->philos[i].im_dead = 0;
		data->philos[i].is_satisfied = 0;
		pthread_mutex_init(&data->philos[i].mutex_im_dead, NULL);
		pthread_mutex_init(&data->philos[i].mutex_meals, NULL);
		pthread_mutex_lock(&data->philos[i].mutex_meals);
		data->philos[i].last_meal_time = get_time();
		pthread_mutex_unlock(&data->philos[i].mutex_meals);
		i++;
	}
	return (1);
}

int	ft_create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, ft_routine, \
&data->philos[i]) != 0)
		{
			pthread_mutex_lock(&data->start_mutex);
			data->start = -1;
			pthread_mutex_unlock(&data->start_mutex);
			while (--i >= 0)
				pthread_join(data->philos[i].thread, NULL);
			return (0);
		}
		i++;
	}
	return (1);
}
