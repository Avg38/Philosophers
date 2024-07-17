/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:44:01 by avialle-          #+#    #+#             */
/*   Updated: 2024/07/11 13:03:59 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdint.h>
# include <limits.h>
# include <errno.h>
# include <stdbool.h>

/**COLOR**/
# define RED "\e[0;31m"
# define WHITE "\x1b[37;1m"
# define RESET "\x1b[0m"
# define GREEN "\e[0;32m"

/**MSG_ERROR**/
# define ERR_MALLOC "Error: Memory allocation failed with malloc.\n"
# define ERR_PHILO_NBR "Invalid philosophers number\n"
# define ERR_TIME_DIE "Invalid time to die\n"
# define ERR_TIME_EAT  "Invalid time to eat\n"
# define ERR_TIME_SLEEP "Invalid time to sleep\n"
# define ERR_TIME_EAT_PER_PHILO "Invalid number of times \
each philosopher must eat\n"
# define ERR_ARG_NBR "Error: Invalid number of arguments\n"

/**Max philo**/
# define PHILO_MAX 200

/**define status code to manage mutex and thread errors**/
typedef enum e_code
{
	JOIN,
	CREATE,
	INIT,
	LOCK,
	UNLOCK,
	DESTROY,
	LONELY_PHILO
}	t_code;

typedef struct s_rules	t_rules;
typedef pthread_mutex_t	t_mtx;

/**Structures**/
typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	bool			is_full;
	long			last_meal;
	t_mtx			philo_lock;
	bool			*first_fork;
	bool			*second_fork;
	int				first_fork_id;
	int				second_fork_id;
	t_rules			*rules;
}					t_philo;

typedef struct s_rules
{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			philo_nbr;
	long			max_meals;
	long			start_time;
	long			threads_running_nbr;
	bool			thread_ready;
	bool			dead_flag;
	bool			*forks;
	t_mtx			*mtx_forks;
	t_mtx			mtx_rules;
	t_mtx			write_lock;
	t_philo			*philos;
}					t_rules;

// -------------- check_args.c --------------
bool	check_args(int argc, char **argv);

// -------------- diner_routine.c --------------
void	print_message(t_rules *rules, char *str, int id);
void	think(t_philo *philo, t_rules *rules);
void	dream(t_philo *philo, t_rules *rules);
void	eat(t_rules *rules, t_philo *philo);

// -------------- handle_errors.c --------------
void	print_error(char *msg);
void	ft_putstr_fd(char *str, uint8_t fd);
void	exit_and_clean(t_rules *rules, t_philo *philo);

// -------------- handle_mutex_and_thread.c --------------
void	handle_mutex(t_mtx *mutex, t_code mtxcode);
void	handle_thread(t_philo *philo, t_code code);
void	wait_all_threads(t_rules *rules);

// -------------- init_simulation.c --------------
void	*lonely_philo(void *arg);
bool	dead_loop(t_rules *rules);
void	*diner_loop(void *pointer);
void	init_simulation(t_rules *rules, t_philo *philos);
void	pre_desynchronize(t_philo *philo);
void	keep_desynchronize(t_philo *philos);

// ------------------- init.c -------------------
void	init_rules(t_rules *rules, t_philo *philos, char **argv);
void	init_forks(t_rules *rules, int philo_nbr);
void	init_philos(t_philo *philos, t_rules *rules);

// -------------- monitor.c --------------
void	last_print(t_rules *rules, int id);
bool	is_end_condition(t_rules *rules);
bool	all_threads_running(t_mtx *mutex, long *threads, \
long philo_nbr);
void	*monitor(void *pointer);

// -------------- mutex_access.c --------------
bool	get_mtxbool(t_mtx *mutex, bool *to_get);
void	set_mtxbool(t_mtx *mutex, bool *to_set, bool value);
long	get_mtxlong(t_mtx *mutex, long *to_get);
void	set_mtxlong(t_mtx *mutex, long *to_set, long value);
void	increase_long(t_mtx *mutex, long *value);

// -------------- struct_allocation.c --------------
void	free_data(t_rules **rules, t_philo **philos);
void	*ft_calloc(size_t nmemb, size_t size);
bool	allocate_struct(t_rules **rules, t_philo **philos, int philo_nbr);

// -------------- time.c --------------
long	get_time(void);
void	precise_sleep(t_rules *rules, long usec);
long	get_elapsed_time(long timestamp_start);
void	ms_sleep(long ms);

// -------------- utils.c --------------
uint8_t	is_digit(const char *s);
uint8_t	ft_isspace(char c);
int		ft_strlen(char *str);
long	ft_atol(const char *s);

#endif