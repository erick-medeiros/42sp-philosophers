/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 10:42:43 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/19 16:50:38 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>     // for O_* constants
# include <pthread.h>   // thread...
# include <semaphore.h> // semaphores ...
# include <signal.h>    // kill
# include <stdio.h>     // printf
# include <stdlib.h>    // malloc, free, exit
# include <string.h>    // memset
# include <sys/time.h>  // gettimeofday
# include <sys/wait.h>  // waitpid
# include <unistd.h>    // write, fork, usleep

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
	sem_t		*lock_log;
	sem_t		*lock_dinner;
	sem_t		*dinner_is_over;
	sem_t		*lock_ate;
	sem_t		*all_ate;
	sem_t		*forks;
	t_philo		*philosophers;
};

struct s_philo
{
	pid_t		pid;
	int			id;
	int			num;
	pthread_t	monitor_tid;
	pthread_t	dinner_tid;
	t_msec		last_meal_time;
	int			amount_of_meals;
	char		*sem_name;
	sem_t		*lock_meal;
	t_data		*data;
};

// init
t_bool	check_arguments(int argc, char *argv[]);
t_bool	init_data(t_data *data, int argc, char *argv[]);
sem_t	*new_semaphore(const char *name, unsigned int value);
char	*philo_sem_name(char *name, int philo_num);

// destroy
void	destroy_data(t_data *data, t_bool delete_sem);
void	destroy_semaphore(const char *name, sem_t *sem);

// routine
void	philo_routine(t_philo *philo);
void	*dinner_routine(void *arg);
int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		philo_think(t_philo *philo);
void	*monitor_routine(void *arg);

// dinner
void	update_info_of_meal(t_philo *philo);
void	ate_the_mandatory_meals(t_philo *philo);
t_msec	get_last_meal_time(t_philo *philo);
void	*all_ate_routine(void *arg);

// finish
t_bool	dinner_is_over(t_data *data);
void	finish_dinner(t_data *data);
void	exit_error(t_data *data, t_bool delete_sem, char *msg);

// logs
void	state_log(t_data *data, int philo_num, t_state state);

// utils
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_mssleep(t_msec ms);
t_msec	timestamp_in_ms(void);
void	ft_putstr_fd(char *s, int fd);

// string libft
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);

#endif
