/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:33:12 by guclemen          #+#    #+#             */
/*   Updated: 2025/06/19 18:02:28 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_print_error("Invalid number of inputs\n", 1));
	if (!ft_isallnum(argc, argv))
		return (ft_print_error("All arguments must be positive numbers\n", 1));
	build_data(&data, argc, argv);
	if (!ft_create_forks(&data))
		return (ft_print_error("Initializing mutex for fork\n", 1));
	if (!ft_create_philos(&data))
		return (ft_print_error("Initializing philosophers failed\n", 1));
	return (0);
}
