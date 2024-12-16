/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:40:29 by niperez           #+#    #+#             */
/*   Updated: 2024/12/14 14:56:07 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_atol(const char *str)
{
	long	nb;

	nb = 0;
	while ((9 <= *str && *str <= 13) || *str == ' ')
		str++;
	while (*str == '+')
		str++;
	if (*str == '-')
		return (printf("Error: arg < 0\n"), -1);
	while ('0' <= *str && *str <= '9')
	{
		nb = (10 * nb) + (*str - '0');
		str++;
		if (nb > INT_MAX)
			return (printf("Error: arg > INT_MAX\n"), -1);
	}
	return (nb);
}

static int	input(t_config *config, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("Error: argument number\n"), 1);
	config->num_philos = (int)ft_atol(argv[1]);
	config->data = malloc(sizeof(t_data));
	if (config->data == NULL)
		return (printf("Error: memory allocation data\n"), 1);
	config->data->time_to_die = ft_atol(argv[2]);
	config->data->time_to_eat = ft_atol(argv[3]);
	config->data->time_to_sleep = ft_atol(argv[4]);
	if (config->num_philos < 0 || config->data->time_to_die < 0
		|| config->data->time_to_eat < 0 || config->data->time_to_sleep < 0)
		return (1);
	if (config->num_philos == 0 || config->data->time_to_die == 0
		|| config->data->time_to_eat == 0 || config->data->time_to_sleep == 0)
		return (printf("error: invalid argument ou arg = 0\n"), 1);
	if (argc == 6)
	{
		config->data->must_eat_count = (int)ft_atol(argv[5]);
		if (config->data->must_eat_count < 0)
			return (1);
	}
	else
		config->data->must_eat_count = -1;
	config->data->end = false;
	return (0);
}

static int	malloc_tabs(t_config *config)
{
	config->forks = malloc(config->num_philos * sizeof(pthread_mutex_t));
	if (config->forks == NULL)
	{
		printf("Error: memory allocation forks\n");
		return (free(config->data), 1);
	}
	config->philos = malloc(config->num_philos * sizeof(t_philo));
	if (config->philos == NULL)
	{
		printf("Error: memory allocation philos\n");
		return (free(config->data), free(config->forks), 1);
	}
	return (0);
}

int	parse(t_config *config, int argc, char **argv)
{
	return (input(config, argc, argv) || malloc_tabs(config));
}
