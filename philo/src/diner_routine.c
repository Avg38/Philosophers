/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:09:06 by avialle-          #+#    #+#             */
/*   Updated: 2024/06/25 16:50:58 by avialle-         ###   ########.fr       */
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

void	think(t_philo *philo, t_rules *rules)
{
	long	t_think;

	print_message(rules, "is thinking", philo->id);
	if (rules->philo_nbr % 2 == 0)
		return ;
	t_think = (rules->time_to_eat * 2) - rules->time_to_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_sleep(rules, t_think * 0.10);
}

void	dream(t_philo *philo, t_rules *rules)
{
	print_message(rules, "is sleeping", philo->id);
	precise_sleep(rules, rules->time_to_sleep);
}

void	eat(t_rules *rules, t_philo *philo)
{
	while (get_mtxbool(&rules->mtx_forks[philo->first_fork_id], philo->first_fork)
		|| get_mtxbool(&rules->mtx_forks[philo->second_fork_id], philo->second_fork))
		usleep(100);
	set_mtxbool(&rules->mtx_forks[philo->first_fork_id], philo->first_fork, true);
	set_mtxbool(&rules->mtx_forks[philo->second_fork_id], philo->second_fork, true);
	print_message(philo->rules, "has taken a fork", philo->id);
	print_message(philo->rules, "has taken a fork", philo->id);
	philo->meals_eaten++;
	set_mtxlong(&philo->philo_lock, &philo->last_meal, get_time());
	print_message(philo->rules, "is eating", philo->id);
	precise_sleep(philo->rules, philo->rules->time_to_eat);
	if (philo->meals_eaten == philo->rules->max_meals)
		set_mtxbool(&philo->philo_lock, &philo->is_full, true);
	set_mtxbool(&rules->mtx_forks[philo->second_fork_id], philo->second_fork, false);
	set_mtxbool(&rules->mtx_forks[philo->first_fork_id], philo->first_fork, false);
	// philo->first_fork = false;
	// philo->second_fork = false;
	// handle_mutex(&rules->mtx_forks[philo->second_fork_id], UNLOCK);
	// handle_mutex(&rules->mtx_forks[philo->first_fork_id], UNLOCK);
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
		eat(rules, philo);
		dream(philo, rules);
		think(philo, rules);
		if (rules->philo_nbr % 2 != 0 && rules->philo_nbr < 31)
			keep_desynchronize(philo);
	}
	return (pointer);
}
