/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:21:38 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/16 17:23:42 by avialle-         ###   ########.fr       */
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

# define PHILO_MAX 200

typedef enum e_code
{
	JOIN,
	CREATE,
	INIT,
	LOCK,
	UNLOCK,
	DESTROY,
	DETACH,
	LONE_PHILO,
}	t_code;

typedef struct s_rules	t_rules;
typedef pthread_mutex_t	t_mtx;

/**Structures**/
typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			meals_eaten;
	bool		is_full;
	long		last_meal;
	t_mtx		philo_lock;
	t_mtx		*first_fork;
	t_mtx		*second_fork;
	t_rules		*rules;
}	t_philo;

typedef struct s_rules
{
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	philo_nbr;
	long	max_meals;
	long	start_time;
	long	threads_running_nbr;
	bool	thread_ready;
	bool	dead_flag;
	t_mtx	mtx_rules;
	t_mtx	write_lock;
	t_philo	*philos;
}	t_rules;

// -------------- check_args.c --------------
bool		check_args(int ac, char **av);

// -------------- diner_routine.c --------------
void		print_message(t_rules *rules, char *str, int id);
void		think(t_rules *rules, t_philo *philo, bool pre_sim);
void		dream(t_rules *rules, t_philo *philos);
void		eat(t_philo *philo);

// -------------- handle_errors.c --------------
void		exit_and_clean(t_rules *rules, t_mtx *forks, t_philo *philos);
void		ft_putstr_fd(char *str, int fd);
void		print_error(char *msg);

// -------------- handle_mutex.c --------------
void		handle_mutex(t_mtx *mutex, t_code mtx_code);

// -------------- handle_thread.c --------------
void		handle_thread(t_philo *philos, t_code code);
void		wait_all_threads(t_rules *rules);

// -------------- init_simulation.c --------------
void		*lone_philo(void *arg);
bool		dead_loop(t_rules *rules);
void		*diner_loop(void *pointer);
void		init_simulation(t_rules *rules, t_mtx *forks, t_philo *philos);

// ------------------- init.c -------------------
void		init_philos(t_rules *rules, t_mtx *forks, t_philo *philos);
void		init_forks(t_mtx *forks, int philo_nbr);
void		init_rules(t_rules *rules, t_philo *philos, char **av);

// -------------- monitor.c --------------
void		last_print(t_rules *rules, int id);
bool		is_end_condition(t_rules *rules);
bool		all_threads_running(t_mtx *mutex, \
	long *threads, long philo_nbr);
void		*monitor(void *pointer);

// -------------- mutex_access.c --------------
bool		get_mtx_bool(t_mtx *mutex, bool *to_get);
void		set_mtx_bool(t_mtx *mutex, bool *to_set, bool value);
long		get_mtx_long(t_mtx *mutex, long *to_get);
void		set_mtx_long(t_mtx *mutex, long *to_set, long value);
void		increase_long(t_mtx *mutex, long *value);

// -------------- struct_allocation.c --------------
void		free_data(t_rules **rules, t_mtx **forks, t_philo **philos);
void		*ft_calloc(size_t nmemb, size_t size);
bool		allocate_struct(t_rules **rules, \
	t_mtx **forks, t_philo **philos, int philo_nbr);

// -------------- time.c --------------
long		get_elapsed_time_ms(long timestamp_start);
long		get_time(void);
void		precise_sleep(t_rules *rules, long ms);

// -------------- utils.c --------------
int			is_digit(const char *s);
int			ft_isspace(char c);
int			ft_strlen(char *str);
long		ft_atol(const char *s);

#endif