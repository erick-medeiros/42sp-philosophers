/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 10:41:45 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/19 16:48:18 by eandre-f         ###   ########.fr       */
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
	i = -1;
	while (++i < data.num_of_philos)
		waitpid(data.philosophers[i].pid, NULL, 0);
	destroy_data(&data, TRUE);
	return (EXIT_SUCCESS);
}
