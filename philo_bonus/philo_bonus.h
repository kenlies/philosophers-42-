/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aotsala <aotsala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:39:51 by aotsala           #+#    #+#             */
/*   Updated: 2023/06/08 05:33:44 by aotsala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <signal.h>

# define MAX_INT 2147483647

typedef struct s_philo	t_philo;
typedef struct s_info	t_info;

typedef struct s_info
{
	int				stop;
	int				philos_have_eaten;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_must_eat;
	long long		start_time_mil;
	t_philo			*philo_struct;
	sem_t			*forkpile;
	sem_t			*stopped;
	sem_t			*printing;
	sem_t			*eating;
}				t_info;

typedef struct s_philo
{
	int				id;
	int				meal_count;
	int				is_eating;
	long long		last_meal;
	t_info			*info;
	pthread_t		death_runner;
	pid_t			p_id;
}				t_philo;

long long	ft_atoi(const char *str);
int			ft_isdigit(char c);
long long	ft_get_time(void);
void		ft_echo_philo(t_philo *philo_struct, char *msg);
void		ft_bad_sleeper(long long t);

void		executer(t_info *info);
void		*death_runner(void *philo);
void		fill_philo_struct_init_sems(t_info *info, int i);
int			init_sems_and_philos(t_info *info);

void		routine(void *arg);
int			eat_sleep_think(t_philo *curr_philo);
void		*death_sentence(void *arg);

void		errors(char *msg);
char		*ft_itoa(int n);
char		*ft_strcat(char *dest, char *src);

#endif