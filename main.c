/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:33:12 by guclemen          #+#    #+#             */
/*   Updated: 2025/07/11 16:27:08 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (ft_error("Invalid number of inputs\n", 1, NULL));
	if (!ft_isallnum(argc, argv))
		return (ft_error("All arguments must be positive numbers\n", 1, NULL));
	build_data(&data, argc, argv);
	if (!ft_create_forks(&data))
		return (ft_error("Initializing mutex for fork\n", 1, &data));
	if (!ft_build_philos_data(&data))
		return (ft_error("Initializing philosophers failed\n", 1, &data));
	if (!ft_create_threads(&data))
		return (ft_error("Creating threads failed\n", 1, &data));
	if (pthread_create(&data.monitor, NULL, ft_monitor, &data) != 0)
		return (ft_error("Creating monitor failed\n", 1, &data));
	data.start_time = get_time();
	pthread_mutex_lock(&data.start_mutex);
	data.start = 1;
	pthread_mutex_unlock(&data.start_mutex);
	while (i < data.num_philos)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	pthread_join(data.monitor, NULL);
	return (ft_error(NULL, 0, &data));
}
