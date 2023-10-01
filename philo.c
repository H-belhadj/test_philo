/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:42:14 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/10/01 18:01:21 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	short_cena(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat);
	if (philo->data->number_of_times_each_philosopher_must_eat > 0 
		&& philo->data->finish >= philo->data->number_of_philosophers)
	{
		pthread_mutex_lock(&philo->data->is_end_t);
		philo->data->is_end = 1;
		pthread_mutex_unlock(&philo->data->is_end_t);
		printf("ALL THE PHILOSOPHERS ARE EAT %d TIME\n",
			philo->data->number_of_times_each_philosopher_must_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->eat);
	return (0);
}

int	sort_cena_2(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->die);
	if (timer() - philo->last_eat >= philo->data->time_to_die 
		&& time_cur(philo) % philo->data->time_to_die == 0)
	{
		pthread_mutex_lock(&philo->data->write);
		pthread_mutex_lock(&philo->data->is_end_t);
		philo->data->is_end = 1;
		pthread_mutex_unlock(&philo->data->is_end_t);
		pthread_mutex_unlock(&philo->data->write);
		ft_print("died\n", philo);
		pthread_mutex_unlock(&philo->data->die);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->die);
	return (0);
}

void	cena(t_philo *philo)
{
	int	i;
	t_philo *tmp;

	tmp = philo;
	i = 0;
	while (i < tmp->data->number_of_philosophers)
	{
		pthread_create(&tmp->thread, NULL, &diner, tmp);
		usleep(100);
		tmp = tmp->next;
		i++;
	}
	tmp = philo;
	while (1)
	{
		if (short_cena(tmp) || sort_cena_2(tmp))
		{
			usleep(100);
			break ;
		}
		tmp = tmp->next;
	}
	i = -1;
	tmp = philo;
	while(++i < tmp->data->number_of_philosophers)
	{
		usleep(50000);
		pthread_detach(tmp->thread);
		tmp = tmp->next;
	}
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

int	main(int argc, char **argv)
{
	t_list	*list;
	t_philo	*philo;

	philo = NULL;
	list = malloc(sizeof(t_list));
	if (cheack(argc, argv))
		return (1);
	list = arg_value(&list, argc, argv);
	philo = ft_philo(list);
	if (!philo)
		return (1);
	cena(philo);
	return (0);
}
