/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:02:19 by avialle-          #+#    #+#             */
/*   Updated: 2024/06/25 11:00:47 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	exit_and_clean(t_rules *rules, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < rules->philo_nbr)
	{
		handle_thread(&philo[i], JOIN);
		handle_mutex(&philo[i].philo_lock, DESTROY);
	}
	handle_mutex(&rules->write_lock, DESTROY);
	handle_mutex(&rules->mtx_rules, DESTROY);
	i = -1;
	while (++i < rules->philo_nbr)
		handle_mutex(&rules->mtx_forks[i], DESTROY);
	free_data(&rules, &philo);
}

void	ft_putstr_fd(char *str, uint8_t fd)
{
	if (str)
		write(fd, str, ft_strlen(str));
}

void	print_error(char *msg)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(RESET, 2);
}
