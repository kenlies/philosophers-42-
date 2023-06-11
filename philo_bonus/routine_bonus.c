/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aotsala <aotsala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:39:51 by aotsala           #+#    #+#             */
/*   Updated: 2023/06/08 05:34:18 by aotsala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	eat_sleep_think(t_philo *curr_philo)
{
	sem_wait(curr_philo->info->forkpile);
	ft_echo_philo(curr_philo, "has taken a fork\n");
	sem_wait(curr_philo->info->forkpile);
	ft_echo_philo(curr_philo, "has taken a fork\n");
	sem_wait(curr_philo->info->eating);
	ft_echo_philo(curr_philo, "is eating\n");
	curr_philo->last_meal = ft_get_time();
	sem_post(curr_philo->info->eating);
	ft_bad_sleeper(curr_philo->info->time_to_eat);
	sem_wait(curr_philo->info->eating);
	curr_philo->meal_count++;
	sem_post(curr_philo->info->eating);
	sem_post(curr_philo->info->forkpile);
	sem_post(curr_philo->info->forkpile);
	ft_echo_philo(curr_philo, "is sleeping\n");
	ft_bad_sleeper(curr_philo->info->time_to_sleep);
	ft_echo_philo(curr_philo, "is thinking\n");
	return (0);
}

void	check_meal_count(t_philo *phil)
{
	if (phil->meal_count >= phil->info->philo_must_eat
		&& phil->info->philo_must_eat)
	{
		sem_post(phil->info->eating);
		usleep(200);
		exit(0);
	}
}

void	*death_runner(void *philo)
{
	t_philo	*phil;

	phil = (t_philo *)philo;
	while (42)
	{
		sem_wait(phil->info->eating);
		if ((ft_get_time() - phil->last_meal) > (phil->info->time_to_die))
		{
			usleep(200);
			ft_echo_philo(phil, "died\n");
			sem_wait(phil->info->stopped);
			phil->info->stop = 1;
			sem_post(phil->info->stopped);
			sem_wait(phil->info->printing);
			exit(1);
		}
		sem_post(phil->info->eating);
		usleep(1000);
		sem_wait(phil->info->eating);
		check_meal_count(phil);
		sem_post(phil->info->eating);
	}
	return (NULL);
}

void	routine(void *arg)
{
	t_philo	*curr_philo;

	curr_philo = (t_philo *)arg;
	if (curr_philo->id % 2)
		usleep(10000);
	if (pthread_create(&curr_philo->death_runner,
			NULL, death_runner, curr_philo) != 0)
		errors("Failed to create death_runner thread\n");
	while (42)
		eat_sleep_think(curr_philo);
	if (pthread_detach(curr_philo->death_runner) != 0)
		errors("Failed to detach death runner thread\n");
}
