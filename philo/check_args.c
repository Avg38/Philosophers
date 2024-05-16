/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:12:13 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/16 17:22:16 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_max_or_empty(char *content)
{
	int	len;
	int	value;

	len = ft_strlen(content);
	if (len > 10 || len == 0)
		return (false);
	value = ft_atol(content);
	if (value > INT_MAX || value < INT_MIN)
		return (false);
	return (true);
}

static bool	check_content(char *content)
{
	if (!check_max_or_empty(content))
		return (false);
	if (!(is_digit(content)))
		return (false);
	return (true);
}

static bool	check_syntax_and_size(char **av)
{
	if (ft_atol(av[1]) > PHILO_MAX || ft_atol(av[1]) <= 0
		|| !check_content(av[1]))
		return (print_error(ERR_PHILO_NBR), false);
	if (!check_content(av[2]))
		return (print_error(ERR_TIME_DIE), false);
	if (!check_content(av[3]))
		return (print_error(ERR_TIME_EAT), false);
	if (!check_content(av[4]))
		return (print_error(ERR_TIME_SLEEP), false);
	if (av[5] && !check_content(av[5]))
		return (print_error(ERR_TIME_EAT_PER_PHILO), false);
	return (true);
}

bool	check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (print_error(ERR_ARG_NBR), false);
	if (!check_syntax_and_size(av))
		return (false);
	return (true);
}
