/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:12:10 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/16 16:47:08 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_elapsed_time_ms(long timestamp_start)
{
	return (get_time() - timestamp_start);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	precise_sleep(t_rules *rules, long ms)
{
	long	start_time;

	start_time = get_time();
	(void)rules;
	while ((get_time() - start_time) < ms)
		usleep(100);
}
