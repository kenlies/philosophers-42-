/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aotsala <aotsala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:39:51 by aotsala           #+#    #+#             */
/*   Updated: 2023/06/09 12:48:00 by aotsala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse(char **argv, t_info *info)
{
	if ((ft_atoi(argv[1]) > MAX_INT) || (ft_atoi(argv[2]) > MAX_INT)
		|| (ft_atoi(argv[3]) > MAX_INT) || (ft_atoi(argv[4]) > MAX_INT))
		return (-1);
	info->philo_count = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		if ((ft_atoi(argv[5]) > MAX_INT) || (ft_atoi(argv[5]) == 0))
			return (-1);
		info->philo_must_eat = ft_atoi(argv[5]);
	}
	if (info->philo_count == 0)
		return (-1);
	return (0);
}

int	is_only_nums(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][0] == '+')
			{
				j++;
				continue ;
			}
			if (!ft_isdigit(argv[i][j]))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

void	executer(t_info *info)
{
	int	i;

	if (create_threads_mutexes(info) == -1)
	{
		write(2, "Error allocing memory or creating threads\n", 42);
		return ;
	}
	death_runner(info);
	i = 0;
	while (i < info->philo_count)
	{
		pthread_join(info->philo_struct[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < info->philo_count)
		pthread_mutex_destroy(&info->philo_struct[i++].l_fork);
	pthread_mutex_destroy(&info->printing);
	pthread_mutex_destroy(&info->eating);
	pthread_mutex_destroy(&info->stopped);
	free(info->philo_struct);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc == 5 || argc == 6)
	{
		memset(&info, 0, sizeof(t_info));
		if (parse(argv, &info) == -1)
		{
			write(2, "Error parsing\n", 14);
			return (1);
		}
		if (is_only_nums(argv) == -1)
		{
			write(2, "Error parsing\n", 14);
			return (1);
		}
		executer(&info);
	}
	else
	{
		write(2, "Problematic argument count\n", 27);
		return (1);
	}
	return (0);
}
