/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:09:06 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/29 13:52:49 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_message(t_rules *rules, char *str, int id)
{
	long	time;

	handle_mutex(&rules->write_lock, LOCK);
	time = get_time() - rules->start_time;
	if (!dead_loop(rules))
		printf(GREEN"%ld %d %s\n"RESET, time, id, str);
	handle_mutex(&rules->write_lock, UNLOCK);
}

void	think(t_philo *philo, t_rules *rules, bool pre_sim)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (pre_sim == false)
		print_message(rules, "is thinking", philo->id);
	if (rules->philo_nbr % 2 == 0)
		return ;
	t_eat = rules->time_to_eat;
	t_sleep = rules->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_sleep(rules, t_think * 0.10);
}

void	dream(t_philo *philo, t_rules *rules)
{
	print_message(rules, "is sleeping", philo->id);
	precise_sleep(rules, rules->time_to_sleep);
}

void	eat(t_philo *philo)
{
	handle_mutex(philo->first_fork, LOCK);
	handle_mutex(philo->second_fork, LOCK);
	print_message(philo->rules, "has taken a fork", philo->id);
	print_message(philo->rules, "has taken a fork", philo->id);
	philo->meals_eaten++;
	set_mtxlong(&philo->philo_lock, &philo->last_meal, get_time());
	print_message(philo->rules, "is eating", philo->id);
	precise_sleep(philo->rules, philo->rules->time_to_eat);
	if (philo->meals_eaten == philo->rules->max_meals)
		set_mtxbool(&philo->philo_lock, &philo->is_full, true);
	handle_mutex(philo->first_fork, UNLOCK);
	handle_mutex(philo->second_fork, UNLOCK);
}

void	*diner_loop(void *pointer)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)pointer;
	rules = philo->rules;
	wait_all_threads(rules);
	increase_long(&rules->mtx_rules, &rules->threads_running_nbr);
	set_mtxlong(&philo->philo_lock, &philo->last_meal, rules->start_time);
	pre_desynchronize(philo);
	while (!dead_loop(rules))
	{
		eat(philo);
		dream(philo, rules);
		think(philo, rules, false);
	}
	return (pointer);
}
