/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:14:07 by fdarrin           #+#    #+#             */
/*   Updated: 2021/04/10 15:34:29 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int	print(t_ph *ph, int message)
{
	if (ph->info->dead || (ph->info->meals && ph->meals == ph->info->meals))
		return (EXIT_FAILURE);
	pthread_mutex_lock(&ph->info->mutex_print);
	printf("%d %d %s", (int)(current_time() - ph->info->start), ph->number, \
		get_message(message));
	pthread_mutex_unlock(&ph->info->mutex_print);
	return (EXIT_SUCCESS);
}

void	take_meal(t_ph *ph)
{
	if (ph->info->dead || (ph->info->meals && ph->meals == ph->info->meals))
		return ;
	pthread_mutex_lock(ph->left_fork);
	print(ph, FORK);
	pthread_mutex_lock(ph->right_fork);
	print(ph, FORK);
	pthread_mutex_lock(&ph->info->mutex);
	ph->last_meal = current_time() + ph->info->time_to_die;
	print(ph, EAT);
	pthread_mutex_unlock(&ph->info->mutex);
	ph->meals += 1;
	my_usleep(ph->info->time_to_eat);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	print(ph, SLEEP);
	my_usleep(ph->info->time_to_sleep);
}

void	*check_work(void *v_ph)
{
	t_info	*info;
	t_ph	*ph;

	ph = (t_ph *)v_ph;
	info = ph->info;
	pthread_detach(ph->check_thread);
	while (info->meals == 0 || info->meals != ph->meals)
	{
		pthread_mutex_lock(&info->mutex);
		if (current_time() > ph->last_meal)
		{
			print(ph, DEAD);
			info->dead = 1;
			pthread_mutex_unlock(&info->mutex);
			break ;
		}
		pthread_mutex_unlock(&info->mutex);
		usleep(1000);
	}
	return ((void *)EXIT_SUCCESS);
}

void	*work(void *v_ph)
{
	t_info		*info;
	t_ph		*ph;
	int			time;

	time = current_time();
	if (time == 1)
		return ((void *)EXIT_FAILURE);
	ph = (t_ph *)v_ph;
	info = ph->info;
	ph->last_meal = time + ph->info->time_to_die;
	if (pthread_create(&ph->check_thread, NULL, &check_work, v_ph))
		return ((void *)EXIT_FAILURE);
	if (ph->number % 2 == 0)
		my_usleep(info->time_to_eat);
	while (ph->info->dead == 0)
	{
		if (ph->info->meals == 0 || ph->info->meals != ph->meals)
		{
			take_meal(ph);
			print(ph, THINK);
		}
		else
			break ;
	}
	return ((void *)EXIT_SUCCESS);
}

int	start(t_ph **ph)
{
	int	i;

	i = 0;
	(*ph)->info->start = current_time();
	if ((*ph)->info->start == 1)
		return (EXIT_FAILURE);
	while (i < (*ph)->info->sum)
	{
		if (pthread_create(&(*ph + i)->thread, NULL, &work, (void *)(*ph + i)))
			return (ERR_THREAD);
		i++;
	}
	return (EXIT_SUCCESS);
}
