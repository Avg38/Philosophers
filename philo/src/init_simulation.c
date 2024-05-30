/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:42:28 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/29 13:50:55 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*lonely_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->rules);
	set_mtxlong(&philo->philo_lock, &philo->last_meal, get_time());
	increase_long(&philo->rules->mtx_rules, &philo->rules->threads_running_nbr);
	print_message(philo->rules, "has taken a fork", philo->id);
	while (!dead_loop(philo->rules))
		precise_sleep(philo->rules, 200);
	return (NULL);
}

bool	dead_loop(t_rules *rules)
{
	return (get_mtxbool(&rules->mtx_rules, &rules->dead_flag));
}

void	pre_desynchronize(t_philo *philo)
{
	if (philo->id % 2 == 0)
		precise_sleep(philo->rules, 0.9 * philo->rules->time_to_sleep);
}

void	init_simulation(t_rules *rules, t_mtx *forks, t_philo *philos)
{
	pthread_t	observator;
	int			i;

	i = 0;
	if (rules->max_meals == 0)
		return (exit_and_clean(rules, forks, philos));
	else if (rules->philo_nbr == 1)
		handle_thread(&rules->philos[i], LONELY_PHILO);
	else
	{
		while (i < rules->philo_nbr)
		{
			handle_thread(&rules->philos[i], CREATE);
			i++;
		}
	}
	pthread_create(&observator, NULL, monitor, rules);
	set_mtxlong(&rules->mtx_rules, &rules->start_time, get_time());
	set_mtxbool(&rules->mtx_rules, &rules->thread_ready, true);
	pthread_join(observator, NULL);
	exit_and_clean(rules, forks, philos);
}
