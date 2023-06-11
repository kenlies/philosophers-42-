/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aotsala <aotsala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:39:51 by aotsala           #+#    #+#             */
/*   Updated: 2023/06/09 17:58:28 by aotsala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi(const char *str)
{
	int			i;
	long long	res;
	long long	n;

	i = 0;
	res = 0;
	n = 1;
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32) && str[i])
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n *= -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * n);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long long	ft_get_time(void)
{
	struct timeval	timeval;
	long long		time_mil;

	gettimeofday(&(timeval), NULL);
	time_mil = (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);
	return (time_mil);
}

void	ft_echo_philo(t_philo *philo_struct, char *msg)
{
	long long	time;

	usleep(5);
	pthread_mutex_lock(&philo_struct->info->printing);
	pthread_mutex_lock(&philo_struct->info->stopped);
	time = ft_get_time() - philo_struct->info->start_time_mil;
	if (!philo_struct->info->stop && !philo_struct->info->philos_have_eaten)
		printf("%lld %d %s", time, philo_struct->id, msg);
	pthread_mutex_unlock(&philo_struct->info->stopped);
	pthread_mutex_unlock(&philo_struct->info->printing);
}

void	ft_bad_sleeper(long long t)
{
	long long	c_t;

	c_t = ft_get_time();
	while (42)
	{
		if ((ft_get_time() - c_t) >= t)
			break ;
		usleep(250);
	}
}
