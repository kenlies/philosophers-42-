/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aotsala <aotsala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:39:51 by aotsala           #+#    #+#             */
/*   Updated: 2023/06/09 14:02:43 by aotsala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fill_philo_struct_and_init_mutexes(t_info *info, int i)
{
	static int	j = 0;

	if (j == 0)
	{
		info->start_time_mil = ft_get_time();
		pthread_mutex_init(&info->printing, NULL);
		pthread_mutex_init(&info->eating, NULL);
		pthread_mutex_init(&info->stopped, NULL);
		j = 1;
	}
	pthread_mutex_init(&(info->philo_struct[i].l_fork), NULL);
	info->philo_struct[i].id = i + 1;
	info->philo_struct[i].last_meal = ft_get_time();
	info->philo_struct[i].r_fork = NULL;
	info->philo_struct[i].info = info;
	info->philo_struct[i].meal_count = 0;
}

int	create_threads_mutexes(t_info *info)
{
	int	i;

	i = -1;
	info->philo_struct = malloc(sizeof(t_philo) * info->philo_count);
	if (!info->philo_struct)
		return (-1);
	while (++i < info->philo_count)
	{
		fill_philo_struct_and_init_mutexes(info, i);
		if (info->philo_count == 1)
		{
			if (pthread_create(&info->philo_struct[i].thread,
					NULL, &death_sentence, &(info->philo_struct[i])) != 0)
				return (-1);
			return (0);
		}
		if (i == info->philo_count - 1)
			info->philo_struct[i].r_fork = &info->philo_struct[0].l_fork;
		else
			info->philo_struct[i].r_fork = &info->philo_struct[i + 1].l_fork;
		if (pthread_create(&info->philo_struct[i].thread,
				NULL, &routine, &(info->philo_struct[i])) != 0)
			return (-1);
	}
	return (0);
}

void	have_eaten_question_mark(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&info->eating);
	while ((i < info->philo_count)
		&& (info->philo_struct[i].meal_count >= info->philo_must_eat))
		i++;
	if (i == info->philo_count)
	{
		pthread_mutex_lock(&info->stopped);
		info->philos_have_eaten = 1;
		pthread_mutex_unlock(&info->stopped);
	}
	pthread_mutex_unlock(&info->eating);
}

void	death_runner(t_info *info)
{
	int	i;

	while (!(info->philos_have_eaten))
	{
		i = -1;
		while (++i < info->philo_count && !(info->stop))
		{
			pthread_mutex_lock(&info->eating);
			if ((ft_get_time() - info->philo_struct[i].last_meal)
				> (info->time_to_die))
			{
				usleep(200);
				ft_echo_philo(&info->philo_struct[i], "died\n");
				pthread_mutex_lock(&info->stopped);
				info->stop = 1;
				pthread_mutex_unlock(&info->stopped);
				pthread_mutex_unlock(&info->eating);
				return ;
			}
			pthread_mutex_unlock(&info->eating);
		}
		if (info->philo_must_eat)
			have_eaten_question_mark(info);
	}
}
