/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:54:51 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/28 15:34:28 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_rules	*rules;
	t_philo	*philos;
	t_mtx	*forks;

	if (!check_args(argc, argv))
		return (EXIT_FAILURE);
	if (!allocate_struct(&rules, &philos, &forks, ft_atol(argv[1])))
		return (print_error(ERR_MALLOC), EXIT_FAILURE);
	init_rules(rules, philos, argv);
	init_forks(forks, rules->philo_nbr);
	init_philos(philos, rules, forks);
	init_simulation(rules, forks, philos);
	return (0);
}
