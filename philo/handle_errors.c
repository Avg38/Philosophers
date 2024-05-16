/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:12:19 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/16 16:47:40 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_and_clean(t_rules *rules, t_mtx *forks, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < rules->philo_nbr)
	{
		handle_thread(&philos[i], JOIN);
		handle_mutex(&philos->philo_lock, DESTROY);
	}
	handle_mutex(&rules->write_lock, DESTROY);
	handle_mutex(&rules->mtx_rules, DESTROY);
	i = -1;
	while (++i < rules->philo_nbr)
		handle_mutex(&forks[i], DESTROY);
	free_data(&rules, &forks, &philos);
}

void	ft_putstr_fd(char *str, int fd)
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
