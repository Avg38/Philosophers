/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:02:19 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/27 16:23:04 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_and_clean(t_rules *rules, t_mtx *forks, t_philo *philo)
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
		handle_mutex(&forks[i], DESTROY);
	free_data(&rules, &philo, &forks);
}

void	ft_putstr_fd(char *s, uint8_t fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	print_error(char *s)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(RESET, 2);
}
