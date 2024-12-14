/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:52:47 by niperez           #+#    #+#             */
/*   Updated: 2024/12/14 14:39:08 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_config	config;

	if (parse(&config, argc, argv))
		return (1);
	init(&config);
	dinner(&config);
	clean(&config);
	return (0);
}
