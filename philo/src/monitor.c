/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:48:07 by avialle-          #+#    #+#             */
/*   Updated: 2024/06/25 11:08:59 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	last_print(t_rules *rules, int id)
{
	long long	time;

	handle_mutex(&rules->write_lock, LOCK);
	time = get_time() - rules->start_time;
	printf(RED"%lld %d died\n"RESET, time, id);
	handle_mutex(&rules->write_lock, UNLOCK);
}

bool	is_end_condition(t_rules *rules)
{
	t_philo	*philos;
	bool	is_dead;
	int		nb_full;
	int		i;

	i = -1;
	philos = rules->philos;
	nb_full = 0;
	is_dead = false;
	while (++i < rules->philo_nbr && is_dead == false)
	{
		set_mtxbool(&(philos[i].philo_lock), &is_dead, get_elapsed_time
			(get_mtxlong(&(philos[i].philo_lock), &philos[i].last_meal))
			>= rules->time_to_die);
		if (get_mtxbool(&(philos[i].philo_lock), &philos[i].is_full))
			nb_full++;
		if (is_dead == true || nb_full == rules->philo_nbr)
		{
			set_mtxbool(&rules->mtx_rules, &rules->dead_flag, true);
			if (is_dead)
				last_print(rules, philos[i].id);
		}
	}
	return (is_dead || (nb_full == rules->philo_nbr));
}

bool	all_threads_running(t_mtx *mutex, long *threads, \
long philo_nbr)
{
	bool	ret;

	ret = false;
	handle_mutex(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	handle_mutex(mutex, UNLOCK);
	return (ret);
}

void	*monitor(void *pointer)
{
	t_rules	*rules;

	rules = (t_rules *)pointer;
	while (!all_threads_running(&rules->mtx_rules,
			&rules->threads_running_nbr, rules->philo_nbr))
		;
	while (!is_end_condition(rules))
		usleep(1000);
	return (NULL);
}
