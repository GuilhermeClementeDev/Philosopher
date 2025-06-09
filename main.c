/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guclemen <guclemen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:33:12 by guclemen          #+#    #+#             */
/*   Updated: 2025/06/09 18:25:05 by guclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_print_error("Invalid number of inputs\n", 1));
	if (!ft_isallnum(argc, argv))
		return (ft_print_error("All arguments must be numeric values.\n", 1));
	ft_printf("deu certo\n");
	return (0);
}
