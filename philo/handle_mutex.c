/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:12:22 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/16 17:06:22 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_mutex(t_mtx *mutex, t_code mtx_code)
{
	if (LOCK == mtx_code)
		pthread_mutex_lock(mutex);
	else if (UNLOCK == mtx_code)
		pthread_mutex_unlock(mutex);
	else if (INIT == mtx_code)
		pthread_mutex_init(mutex, NULL);
	else if (DESTROY == mtx_code)
		pthread_mutex_destroy(mutex);
}
