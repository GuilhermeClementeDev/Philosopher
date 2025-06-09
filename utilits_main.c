/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:01:45 by guclemen          #+#    #+#             */
/*   Updated: 2025/06/09 18:24:33 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_error(char *msg, int nbr)
{
	ft_putstr_fd("Error :(\n", 2);
	ft_putstr_fd(msg, 2);
	return (nbr);
}

int	ft_isallnum(int argc, char **argv)
{
	int	i;
	int	size;

	size = argc;
	while (size > 1)
	{
		i = 0;
		if (argv[size - 1][i] == '+' || argv[size - 1][i] == '-')
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
