/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aotsala <aotsala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:39:51 by aotsala           #+#    #+#             */
/*   Updated: 2023/06/07 06:22:32 by aotsala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_sentence(void *arg)
{
	t_philo	*curr_philo;

	curr_philo = (t_philo *)arg;
	ft_echo_philo(curr_philo, "has taken a fork\n");
	ft_bad_sleeper(curr_philo->info->time_to_eat);
	return (NULL);
}

int	eat_sleep_think(t_philo *curr_philo)
{
	pthread_mutex_lock(&curr_philo->l_fork);
	ft_echo_philo(curr_philo, "has taken a fork\n");
	pthread_mutex_lock(curr_philo->r_fork);
	ft_echo_philo(curr_philo, "has taken a fork\n");
	pthread_mutex_lock(&curr_philo->info->eating);
	ft_echo_philo(curr_philo, "is eating\n");
	curr_philo->last_meal = ft_get_time();
	pthread_mutex_unlock(&curr_philo->info->eating);
	ft_bad_sleeper(curr_philo->info->time_to_eat);
	pthread_mutex_lock(&curr_philo->info->eating);
	curr_philo->meal_count++;
	pthread_mutex_unlock(&curr_philo->info->eating);
	pthread_mutex_unlock(curr_philo->r_fork);
	pthread_mutex_unlock(&curr_philo->l_fork);
	pthread_mutex_lock(&curr_philo->info->eating);
	if (curr_philo->info->philos_have_eaten)
	{
		pthread_mutex_unlock(&curr_philo->info->eating);
		return (1);
	}
	pthread_mutex_unlock(&curr_philo->info->eating);
	ft_echo_philo(curr_philo, "is sleeping\n");
	ft_bad_sleeper(curr_philo->info->time_to_sleep);
	ft_echo_philo(curr_philo, "is thinking\n");
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*curr_philo;

	curr_philo = (t_philo *)arg;
	if (curr_philo->id % 2)
		usleep(10000);
	while (42)
	{
		if (eat_sleep_think(curr_philo))
			break ;
		pthread_mutex_lock(&curr_philo->info->stopped);
		if (curr_philo->info->stop)
		{
			pthread_mutex_unlock(&curr_philo->info->stopped);
			break ;
		}
		pthread_mutex_unlock(&curr_philo->info->stopped);
	}
	return (NULL);
}
