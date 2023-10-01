/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:40:27 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/10/01 19:24:34 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_list	*arg_value(t_list **list, int argc, char **argv)
{
	(*list)->number_of_philosophers = ft_atoi(argv[1]);
	(*list)->time_to_die = ft_atoi(argv[2]);
	(*list)->time_to_eat = ft_atoi(argv[3]);
	(*list)->time_to_sleep = ft_atoi(argv[4]);
	(*list)->number_of_times_each_philosopher_must_eat = -1;
	if (argc == 6)
		(*list)->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	(*list)->start_time = timer();
	return (*list);
}

void	destroy_mutex(t_philo *philo)
{
	t_philo		*tmp;
	int			i;

	i = -1;
	tmp = philo;
	while (++i < tmp->data->number_of_philosophers)
	{
		pthread_mutex_destroy(&tmp->fork);
		pthread_mutex_destroy(&tmp->data->die);
		pthread_mutex_destroy(&tmp->data->eat);
		pthread_mutex_destroy(&tmp->data->write);
		pthread_mutex_destroy(&tmp->data->is_end_t);
		tmp = tmp->next;
	}
}

void	detach_treads(t_philo	*philo)
{
	t_philo		*tmp;
	int			i;

	i = -1;
	tmp = philo;
	while (++i < tmp->data->number_of_philosophers)
	{
		usleep(50000);
		pthread_detach(tmp->thread);
		tmp = tmp->next;
	}
}
