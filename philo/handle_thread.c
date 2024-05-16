/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:12:24 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/16 16:47:36 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_thread(t_philo *philos, t_code code)
{
	if (CREATE == code)
		pthread_create(&(philos->thread), NULL, &diner_loop, philos);
	else if (LONE_PHILO == code)
		pthread_create(&(philos->thread), NULL, &lone_philo, philos);
	else if (JOIN == code)
		pthread_join(philos->thread, NULL);
	else if (DETACH == code)
		pthread_detach(philos->thread);
}

void	wait_all_threads(t_rules *rules)
{
	while (!get_mtx_bool(&rules->mtx_rules, &rules->thread_ready))
		;
}
