/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:12:29 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/28 15:34:25 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_philos(t_philo *philos, t_rules *rules, t_mtx *forks)
{
	int	i;

	i = 0;
	while (i < rules->philo_nbr)
	{
		philos[i].id = i + 1;
		philos[i].rules = rules;
		if (philos[i].id % 2 == 0)
		{
			philos[i].second_fork = &forks[i];
			philos[i].first_fork = &forks[(i + 1) % rules->philo_nbr];
		}
		else
		{
			philos[i].first_fork = &forks[i];
			philos[i].second_fork = &forks[(i + 1) % rules->philo_nbr];
		}
		i++;
	}
}

void	init_forks(t_mtx *forks, int philo_nbr)
{
	int	i;

	i = -1;
	while (++i < philo_nbr)
		handle_mutex(&forks[i], INIT);
}

void	init_rules(t_rules *rules, t_philo *philos, char **argv)
{
	rules->philos = philos;
	rules->philo_nbr = (int)ft_atol(argv[1]);
	rules->time_to_die = ft_atol(argv[2]);
	rules->time_to_eat = ft_atol(argv[3]);
	rules->time_to_sleep = ft_atol(argv[4]);
	rules->thread_ready = false;
	if (argv[5])
		rules->max_meals = (int)ft_atol(argv[5]);
	else
		rules->max_meals = -1;
	handle_mutex(&rules->write_lock, INIT);
	handle_mutex(&rules->mtx_rules, INIT);
}