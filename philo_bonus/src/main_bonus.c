/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 10:41:45 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/17 22:54:44 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	int		i;

	if (!check_arguments(argc, argv))
		return (EXIT_FAILURE);
	if (!init_data(&data, argc, argv))
		return (EXIT_FAILURE);
	i = -1;
	while (++i < data.num_of_philos)
	{
		data.philosophers[i].pid = fork();
		if (data.philosophers[i].pid == -1)
			exit_error(&data, TRUE, "philo: fork: failed");
		else if (data.philosophers[i].pid == 0)
			philo_routine(&data.philosophers[i]);
	}
	if (data.must_eat != -1)
		pthread_create(&data.ate_tid, NULL, all_ate_routine, (void *)&data);
	i = -1;
	while (++i < data.num_of_philos)
		waitpid(data.philosophers[i].pid, NULL, 0);
	if (data.must_eat != -1)
		pthread_detach(data.ate_tid);
	destroy_data(&data, TRUE);
	return (EXIT_SUCCESS);
}
