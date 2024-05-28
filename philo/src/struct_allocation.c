/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_allocation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:58:21 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/28 15:34:53 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_data(t_rules **rules, t_philo **philos, t_mtx **forks)
{
	if (*forks)
		free(*forks);
	if (*rules)
		free(*rules);
	if (*philos)
		free(*philos);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (size != 0 && nmemb > (size_t)(-1) / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	return ((void *)memset(ptr, 0, nmemb * size));
}

bool	allocate_struct(t_rules **rules, t_philo **philos
	, t_mtx **forks, int philo_nbr)
{
	*rules = (t_rules *)ft_calloc(1, sizeof(t_rules));
	if (!*rules)
		return (false);
	*philos = (t_philo *)ft_calloc(philo_nbr, sizeof(t_philo));
	if (!*philos)
		return (free_data(rules, philos, forks), false);
	*forks = (t_mtx *)ft_calloc(philo_nbr, sizeof(t_mtx));
	if (!*forks)
		return (free_data(rules, philos, forks), false);
	return (true);
}
