/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:14:31 by guclemen          #+#    #+#             */
/*   Updated: 2025/07/11 15:19:11 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	ft_mutex_print(t_philo *philo, char *msg)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!ft_someone_died(philo))
	{
		time = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", time, philo->id + 1, msg);
	}
	else if (ft_strcmp(msg, "died") == 0)
	{
		time = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", time, philo->id + 1, msg);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}
