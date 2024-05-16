/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:56:26 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/16 16:47:27 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_rules	*rules;
	t_mtx	*forks;
	t_philo	*philos;

	if (!check_args(ac, av))
		return (EXIT_FAILURE);
	if (!allocate_struct(&rules, &forks, &philos, ft_atol(av[1])))
		return (print_error(ERR_MALLOC), EXIT_FAILURE);
	init_rules(rules, philos, av);
	init_forks(forks, rules->philo_nbr);
	init_philos(rules, forks, philos);
	init_simulation(rules, forks, philos);
}
