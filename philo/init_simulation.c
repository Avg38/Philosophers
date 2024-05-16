/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:12:27 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/16 17:23:13 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->rules);
	set_mtx_long(&philo->philo_lock, &philo->last_meal, get_time());
	increase_long(&philo->rules->mtx_rules, &philo->rules->threads_running_nbr);
	print_message(philo->rules, "has taken a fork", philo->id);
	while (!dead_loop(philo->rules))
		precise_sleep(philo->rules, 200);
	return (NULL);
}

bool	dead_loop(t_rules *rules)
{
	return (get_mtx_bool(&rules->mtx_rules, &rules->dead_flag));
}

static void	pre_desynchronize(t_philo *philo)
{
	if (philo->id % 2 == 0)
		precise_sleep(philo->rules, 0.9 * philo->rules->time_to_sleep);
}

void	*diner_loop(void *pointer)
{
	t_rules	*rules;
	t_philo	*philo;

	philo = (t_philo *)pointer;
	rules = philo->rules;
	wait_all_threads(rules);
	increase_long(&rules->mtx_rules, &rules->threads_running_nbr);
	set_mtx_long(&philo->philo_lock, &philo->last_meal, rules->start_time);
	pre_desynchronize(philo);
	while (!dead_loop(rules))
	{
		eat(philo);
		dream(rules, philo);
		think(rules, philo, false);
	}
	return (pointer);
}

void	init_simulation(t_rules *rules, t_mtx *forks, t_philo *philos)
{
	pthread_t	observator;
	int			i;

	i = 0;
	if (rules->max_meals == 0)
		return (exit_and_clean(rules, forks, philos));
	else if (rules->philo_nbr == 1)
		handle_thread(&rules->philos[i], LONE_PHILO);
	else
	{
		while (i < rules->philo_nbr)
		{
			handle_thread(&rules->philos[i], CREATE);
			i++;
		}
	}
	pthread_create(&observator, NULL, monitor, rules);
	set_mtx_long(&rules->mtx_rules, &rules->start_time, get_time());
	set_mtx_bool(&rules->mtx_rules, &rules->thread_ready, true);
	pthread_join(observator, NULL);
	exit_and_clean(rules, forks, philos);
}
