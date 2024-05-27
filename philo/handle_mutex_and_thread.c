/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutex_and_thread.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:23:53 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/27 16:28:07 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_mutex(t_mtx *mutex, t_code mtxcode)
{
	if (LOCK == mtxcode)
		pthread_mutex_lock(mutex);
	else if (UNLOCK == mtxcode)
		pthread_mutex_unlock(mutex);
	else if (INIT == mtxcode)
		pthread_mutex_init(mutex, NULL);
	else if (DESTROY == mtxcode)
		pthread_mutex_destroy(mutex);
}

void	handle_thread(t_philo *philo, t_code code)
{
	if (CREATE == code)
		pthread_create(&(philo->thread), NULL, &diner_loop, philo);
	else if (LONE_PHILO == code)
		pthread_create(&(philo->thread), NULL, &lone_philo, philo);
	else if (JOIN == code)
		pthread_join(philo->thread, NULL);
	else if (DETACH == code)
		pthread_detach(philo->thread);
}

void	wait_all_threads(t_rules *rules)
{
	while (!get_mtxbool(&rules->mtx_rules, &rules->thread_ready))
		;
}
