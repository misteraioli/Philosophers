/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:08:23 by niperez           #+#    #+#             */
/*   Updated: 2025/06/19 13:55:50 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_data
{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	long			start_dinner;
	bool			end;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	message;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	int				meals_eaten;
	long			last_meal_time;
	bool			is_eating;
	pthread_mutex_t	mutex_meals_eaten;
	pthread_mutex_t	mutex_last_meal_time;
	pthread_mutex_t	mutex_is_eating;
	t_data			*data;
}	t_philo;

typedef struct s_config
{
	int				num_philos;
	t_data			*data;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_config;

int		parse(t_config *config, int argc, char **argv);
void	init(t_config *config);
void	dinner(t_config *config);
void	clean(t_config *config);

void	print_message(t_philo *philo, char *msg);

bool	end_detected(t_data *data);
void	monitoring(t_config *config);

long	get_current_time(void);
void	precise_usleep(long time_in_ms, t_data *data);

#endif
