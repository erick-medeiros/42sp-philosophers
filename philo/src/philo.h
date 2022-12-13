/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 10:42:43 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/13 11:34:14 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_bool		t_bool;
typedef struct s_data	t_data;
typedef struct s_philo	t_philo;
typedef pthread_mutex_t	t_mutex;

enum e_bool
{
	FALSE,
	TRUE
};

struct s_data
{
	int		num_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat;
	long	start_time;
	t_mutex	log_mutex;
	t_mutex	*forks;
	t_philo	*philosophers;
};

struct s_philo
{
	int			id;
	int			num;
	pthread_t	tid;
	t_data		*data;
	t_bool		is_dead;
	t_bool		is_pair;
};

// init
t_bool	check_arguments(int argc, char *argv[]);
t_bool	init_data(t_data *data, int argc, char *argv[]);

// destroy
void	destroy_data(t_data *data);

// routine
void	*dinner_routine(void *p);
t_bool	philo_eat(t_philo *philo);
t_bool	philo_think(t_philo *philo);
t_bool	philo_sleep(t_philo *philo);

// logs
void	state_log(t_philo *philo, const char *state);

// utils
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		mssleep(int ms);
long	timestamp_in_ms(void);

#endif
