/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 09:56:35 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/28 15:34:46 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	get_mtxbool(t_mtx *mutex, bool *to_get)
{
	bool	ret;

	handle_mutex(mutex, LOCK);
	ret = *to_get;
	handle_mutex(mutex, UNLOCK);
	return (ret);
}

void	set_mtxbool(t_mtx *mutex, bool *to_set, bool value)
{
	handle_mutex(mutex, LOCK);
	*to_set = value;
	handle_mutex(mutex, UNLOCK);
}

long	get_mtxlong(t_mtx *mutex, long *to_get)
{
	long	ret;

	handle_mutex(mutex, LOCK);
	ret = *to_get;
	handle_mutex(mutex, UNLOCK);
	return (ret);
}

void	set_mtxlong(t_mtx *mutex, long *to_set, long value)
{
	handle_mutex(mutex, LOCK);
	*to_set = value;
	handle_mutex(mutex, UNLOCK);
}

void	increase_long(t_mtx *mutex, long *value)
{
	handle_mutex(mutex, LOCK);
	(*value)++;
	handle_mutex(mutex, UNLOCK);
}
