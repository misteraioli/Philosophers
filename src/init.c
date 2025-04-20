/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:42:30 by niperez           #+#    #+#             */
/*   Updated: 2024/12/14 15:08:42 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	forks_init(t_config *config)
{
	int	i;

	i = -1;
	while (++i < config->num_philos)
		pthread_mutex_init(&config->forks[i], NULL);
}

static void	distrib_forks(int i, t_config *config)
{
	if (i % 2)
	{
		config->philos[i].first_fork = &config->forks[i];
		config->philos[i].second_fork
			= &config->forks[(i + 1) % config->num_philos];
	}
	else
	{
		config->philos[i].second_fork = &config->forks[i];
		config->philos[i].first_fork
			= &config->forks[(i + 1) % config->num_philos];
	}
}

static void	philos_init(t_config *config)
{
	int	i;

	i = -1;
	while (++i < config->num_philos)
	{
		config->philos[i].id = i + 1;
		config->philos[i].meals_eaten = 0;
		config->philos[i].is_eating = false;
		pthread_mutex_init(&config->philos[i].mutex_meals_eaten, NULL);
		pthread_mutex_init(&config->philos[i].mutex_last_meal_time, NULL);
		pthread_mutex_init(&config->philos[i].mutex_is_eating, NULL);
		distrib_forks(i, config);
		config->philos[i].data = config->data;
	}
}

void	init(t_config *config)
{
	pthread_mutex_init(&config->data->end_mutex, NULL);
	pthread_mutex_init(&config->data->message, NULL);
	forks_init(config);
	philos_init(config);
}
