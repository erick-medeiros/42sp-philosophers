/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 10:42:43 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/19 16:53:18 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h> // thread...
# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <string.h> // memset
# include <sys/time.h> // gettimeofday
# include <unistd.h> // usleep, write

typedef enum e_bool		t_bool;
typedef enum e_state	t_state;
typedef struct s_data	t_data;
typedef struct s_philo	t_philo;
typedef pthread_mutex_t	t_mutex;
typedef long			t_msec;

enum e_bool
{
	FALSE,
	TRUE
};

enum e_state
{
	TAKE_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

struct s_data
{
	int			num_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat;
	t_msec		start_time;
	pthread_t	monitor_tid;
	t_bool		dinner_is_over;
	t_mutex		log_mutex;
	int			all_ate;
	t_mutex		all_ate_mutex;
	t_mutex		dinner_mutex;
	t_mutex		*forks;
	t_philo		*philosophers;
};

struct s_philo
{
	int			id;
	int			num;
	pthread_t	tid;
	t_msec		last_meal_time;
	int			amount_of_meals;
	t_mutex		meal_mutex;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	t_mutex		*first_fork;
	t_mutex		*second_fork;
	t_data		*data;
	t_bool		is_pair;
};

// init
t_bool	check_arguments(int argc, char *argv[]);
t_bool	init_data(t_data *data, int argc, char *argv[]);

// destroy
void	destroy_data(t_data *data);

// routine
void	*dinner_routine(void *p);
int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		philo_think(t_philo *philo);
void	*monitor_routine(void *arg);

// dinner
void	update_info_of_meal(t_philo *philo);
void	ate_the_mandatory_meals(t_philo *philo);
t_msec	get_last_meal_time(t_philo *philo);

// finish
t_bool	dinner_is_over(t_data *data);
void	*finish_dinner(t_data *data);
void	*announce_death(t_philo *philo);

// logs
void	state_log(t_philo *philo, t_state state);

// utils
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_mssleep(t_msec ms);
t_msec	timestamp_in_ms(void);

#endif
