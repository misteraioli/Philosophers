/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:16:20 by niperez           #+#    #+#             */
/*   Updated: 2025/06/19 13:22:34 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->message);
	pthread_mutex_lock(&philo->data->end_mutex);
	if (philo->data->end)
	{
		pthread_mutex_unlock(&philo->data->message);
		pthread_mutex_unlock(&philo->data->end_mutex);
		return ;
	}
	printf("%ld %d %s\n", (get_current_time() - philo->data->start_dinner),
		philo->id, msg);
	pthread_mutex_unlock(&philo->data->message);
	pthread_mutex_unlock(&philo->data->end_mutex);
}

bool	end_detection(t_data *data)
{
	pthread_mutex_lock(&data->end_mutex);
	if (data->end == true)
	{
		pthread_mutex_unlock(&data->end_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->end_mutex);
	return (false);
}

static bool	everyone_ate(t_config *config)
{
	int	i;

	if (config->data->must_eat_count == -1)
		return (false);
	i = -1;
	while (++i < config->num_philos)
	{
		pthread_mutex_lock(&config->philos[i].mutex_meals_eaten);
		if (config->philos[i].meals_eaten < config->data->must_eat_count)
		{
			pthread_mutex_unlock(&config->philos[i].mutex_meals_eaten);
			return (false);
		}
		pthread_mutex_unlock(&config->philos[i].mutex_meals_eaten);
	}
	return (true);
}

static void	check_death(t_config *config)
{
	int	i;

	i = -1;
	while (++i < config->num_philos)
	{
		pthread_mutex_lock(&config->philos[i].mutex_is_eating);
		if (!config->philos[i].is_eating)
		{
			pthread_mutex_unlock(&config->philos[i].mutex_is_eating);
			pthread_mutex_lock(&config->philos[i].mutex_last_meal_time);
			if (get_current_time() - config->philos[i].last_meal_time
				> config->data->time_to_die)
			{
				message(&config->philos[i], "died");
				pthread_mutex_lock(&config->data->end_mutex);
				config->data->end = true;
				pthread_mutex_unlock(&config->data->end_mutex);
				pthread_mutex_unlock(&config->philos[i].mutex_last_meal_time);
				break ;
			}
			pthread_mutex_unlock(&config->philos[i].mutex_last_meal_time);
		}
		else
			pthread_mutex_unlock(&config->philos[i].mutex_is_eating);
	}
}

void	monitoring(t_config *config)
{
	while (!end_detection(config->data))
	{
		if (everyone_ate(config))
		{
			pthread_mutex_lock(&config->data->end_mutex);
			config->data->end = true;
			pthread_mutex_unlock(&config->data->end_mutex);
		}
		check_death(config);
	}
}
