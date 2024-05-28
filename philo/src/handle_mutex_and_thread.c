/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutex_and_thread.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:23:53 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/28 15:34:14 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	handle_mutex(t_mtx *mutex, t_code mtxcode)
{
	if (mtxcode == LOCK)
		pthread_mutex_lock(mutex);
	else if (mtxcode == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (mtxcode == INIT)
		pthread_mutex_init(mutex, NULL);
	else if (mtxcode == DESTROY)
		pthread_mutex_destroy(mutex);
}

void	handle_thread(t_philo *philo, t_code code)
{
	if (code == CREATE)
		pthread_create(&(philo->thread), NULL, &diner_loop, philo);
	else if (code == LONELY_PHILO)
		pthread_create(&(philo->thread), NULL, &lonely_philo, philo);
	else if (code == JOIN)
		pthread_join(philo->thread, NULL);
	else if (code == DETACH)
		pthread_detach(philo->thread);
}

void	wait_all_threads(t_rules *rules)
{
	while (!get_mtxbool(&rules->mtx_rules, &rules->thread_ready))
		;
}
