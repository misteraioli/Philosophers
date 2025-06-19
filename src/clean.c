/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:44:51 by niperez           #+#    #+#             */
/*   Updated: 2025/06/19 13:17:51 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	mutex_destroy(t_config *config)
{
	int	i;

	i = -1;
	while (++i < config->num_philos)
	{
		pthread_mutex_destroy(&config->forks[i]);
		pthread_mutex_destroy(&config->philos[i].mutex_meals_eaten);
		pthread_mutex_destroy(&config->philos[i].mutex_last_meal_time);
		pthread_mutex_destroy(&config->philos[i].mutex_is_eating);
	}
	pthread_mutex_destroy(&config->data->message);
	pthread_mutex_destroy(&config->data->end_mutex);
}

static void	free_tabs(t_config *config)
{
	if (config->data != NULL)
		free(config->data);
	if (config->forks != NULL)
		free(config->forks);
	if (config->philos != NULL)
		free(config->philos);
}

void	clean(t_config *config)
{
	mutex_destroy(config);
	free_tabs(config);
}
