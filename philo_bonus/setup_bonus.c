/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aotsala <aotsala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:39:51 by aotsala           #+#    #+#             */
/*   Updated: 2023/06/08 05:36:02 by aotsala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	fill_philo_struct_init_sems(t_info *info, int i)
{
	static int	j = 0;

	if (j == 0)
	{
		sem_unlink("/forkpile");
		info->forkpile = sem_open("/forkpile", O_CREAT, 0644,
				info->philo_count);
		sem_unlink("/stopped");
		info->stopped = sem_open("/stopped", O_CREAT, 0644, 1);
		sem_unlink("/printing");
		info->printing = sem_open("/printing", O_CREAT, 0644, 1);
		sem_unlink("/eating");
		info->eating = sem_open("/eating", O_CREAT, 0644, 1);
		if (info->forkpile == SEM_FAILED || info->stopped == SEM_FAILED
			|| info->printing == SEM_FAILED || info->eating == SEM_FAILED)
			errors("Failed to open semaphores\n");
		j = 1;
	}
	info->philo_struct[i].id = i + 1;
	info->philo_struct[i].last_meal = ft_get_time();
	info->philo_struct[i].info = info;
	info->philo_struct[i].meal_count = 0;
}

int	init_sems_and_philos(t_info *info)
{
	int	i;

	i = 0;
	info->philo_struct = malloc(sizeof(t_philo) * info->philo_count);
	if (!info->philo_struct)
		return (-1);
	info->start_time_mil = ft_get_time();
	while (i < info->philo_count)
	{
		fill_philo_struct_init_sems(info, i);
		i++;
	}
	i = 0;
	while (i < info->philo_count)
	{
		info->philo_struct[i].p_id = fork();
		if (info->philo_struct[i].p_id == -1)
			return (-2);
		if (info->philo_struct[i].p_id == 0)
			routine(&(info->philo_struct[i]));
		usleep(100);
		i++;
	}
	return (0);
}

void	kill_all(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_count)
	{
		kill(info->philo_struct[i].p_id, SIGKILL);
		i++;
	}
	sem_close(info->forkpile);
	sem_close(info->printing);
	sem_close(info->eating);
	sem_close(info->stopped);
	sem_unlink("/forkpile");
	sem_unlink("/printing");
	sem_unlink("/eating");
	sem_unlink("/stopped");
	free(info->philo_struct);
}

void	executer(t_info *info)
{
	int	i;
	int	exits;
	int	ret;

	ret = init_sems_and_philos(info);
	if (ret == -1)
		errors("Failed to malloc\n");
	else if (ret == -2)
	{
		kill_all(info);
		errors("Failed to fork\n");
	}
	i = 0;
	while (i < info->philo_count)
	{
		waitpid(-1, &exits, 0);
		if (exits != 0)
		{
			kill_all(info);
			break ;
		}
		i++;
	}
	exit(0);
}
