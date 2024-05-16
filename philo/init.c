/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:12:33 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/16 16:47:31 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_rules *rules, t_mtx *forks, t_philo *philos)
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

void	init_rules(t_rules *rules, t_philo *philos, char **av)
{
	rules->philos = philos;
	rules->time_to_die = ft_atol(av[2]);
	rules->time_to_eat = ft_atol(av[3]);
	rules->time_to_sleep = ft_atol(av[4]);
	rules->philo_nbr = (int)ft_atol(av[1]);
	rules->thread_ready = false;
	if (av[5])
		rules->max_meals = (int)ft_atol(av[5]);
	else
		rules->max_meals = -1;
	handle_mutex(&rules->write_lock, INIT);
	handle_mutex(&rules->mtx_rules, INIT);
}
