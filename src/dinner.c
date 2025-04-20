/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:43:09 by niperez           #+#    #+#             */
/*   Updated: 2025/04/20 15:59:28 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	message(philo, "has taken a fork");
	pthread_mutex_lock(philo->second_fork);
	message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->mutex_last_meal_time);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->mutex_last_meal_time);
	pthread_mutex_lock(&philo->mutex_is_eating);
	philo->is_eating = true;
	pthread_mutex_unlock(&philo->mutex_is_eating);
	message(philo, "is eating");
	pthread_mutex_lock(&philo->mutex_last_meal_time);
	precise_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(&philo->mutex_last_meal_time);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_lock(&philo->mutex_meals_eaten);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->mutex_meals_eaten);
	pthread_mutex_lock(&philo->mutex_is_eating);
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->mutex_is_eating);
}

static void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_usleep(philo->data->time_to_eat / 2, philo->data);
	while (!end_detection(philo->data))
	{
		message(philo, "is thinking");
		if (end_detection(philo->data))
			break ;
		eating(philo);
		if (end_detection(philo->data))
			break ;
		message(philo, "is sleeping");
		precise_usleep(philo->data->time_to_sleep, philo->data);
	}
	return (NULL);
}

static void	*philosopher_solo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	message(philo, "is thinking");
	pthread_mutex_lock(philo->first_fork);
	message(philo, "has taken a fork");
	return (NULL);
}

void	dinner(t_config *config)
{
	int	i;

	i = -1;
	config->data->start_dinner = get_current_time();
	while (++i < config->num_philos)
		config->philos[i].last_meal_time = config->data->start_dinner;
	if (config->num_philos == 1)
	{
		pthread_create(&config->philos[0].thread, NULL,
			philosopher_solo, &config->philos[0]);
		check_end(config);
		return ;
	}
	i = -1;
	while (++i < config->num_philos)
	{
		pthread_create(&config->philos[i].thread, NULL,
			philosopher_routine, &config->philos[i]);
	}
	check_end(config);
	i = -1;
	while (++i < config->num_philos)
		pthread_join(config->philos[i].thread, NULL);
}
