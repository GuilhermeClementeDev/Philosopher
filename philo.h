/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:39:05 by guclemen          #+#    #+#             */
/*   Updated: 2025/07/01 16:01:15 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "./lib/libft.h"
# include <pthread.h>

struct					s_philo;
typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_times_each_must_eat;
	int				has_meals_limit;
	int				someone_died;
	int				start;
	pthread_mutex_t	start_mutex;
	long long		start_time;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

// utilits_main
int		ft_isallnum(int argc, char **argv);
int		ft_print_error(char *msg, int nbr);
void	build_data(t_data *data, int argc, char **argv);
int		ft_create_forks(t_data *data);
int		ft_build_philos_data(t_data *data);

//threads_utilits
int		ft_create_threads(t_data *data);
int		ft_error(char *msg, int ret, t_data *data);
#endif
