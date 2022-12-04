/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 10:42:43 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/03 20:31:41 by eandre-f         ###   ########.fr       */
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
	t_mutex	log_mutex;
	t_philo	*philosophers;
};

struct s_philo
{
	int			number;
	pthread_t	tid;
};

// libft
int		ft_atoi(const char *str);
int		ft_isdigit(int c);

// init
t_bool	check_arguments(int argc, char *argv[]);
t_bool	init_data(t_data *data, int argc, char *argv[]);

// destroy
void	destroy_data(t_data *data);

// routine
void	*dinner_routine(void *p);

// logs
void	state_log(t_philo *philo, const char *state);

#endif
