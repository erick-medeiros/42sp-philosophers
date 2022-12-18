/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:11:18 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/17 20:03:16 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t	*new_semaphore(const char *name, unsigned int value)
{
	sem_t	*sem;
	int		mode;

	sem_unlink(name);
	mode = S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR;
	sem = sem_open(name, O_CREAT, mode, value);
	if (sem == SEM_FAILED)
	{
		ft_putstr_fd("philo: sem_open: failed\n", 2);
		exit(EXIT_FAILURE);
	}
	return (sem);
}

void	destroy_semaphore(const char *name, sem_t *sem)
{
	sem_close(sem);
	sem_unlink(name);
}

char	*philo_sem_name(char *name, int philo_num)
{
	char	*tmp;
	char	*str;

	tmp = ft_itoa(philo_num);
	str = ft_strjoin(name, tmp);
	free(tmp);
	return (str);
}
