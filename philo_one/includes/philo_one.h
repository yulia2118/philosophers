/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:23:51 by fdarrin           #+#    #+#             */
/*   Updated: 2021/04/10 15:33:03 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DEAD 5
# define ERR_ARGS -2
# define ERR_TIME -3
# define ERR_MALLOC -4
# define ERR_THREAD -5
# define ERR_MUTEX -6

typedef struct s_info
{
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	*frks;
	pthread_mutex_t	mutex;
	int				start;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				sum;
	int				meals;
	int				dead;
}					t_info;

typedef struct s_ph
{
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_t		check_thread;
	pthread_t		thread;
	t_info			*info;
	int				last_meal;
	int				meals;
	int				number;
}					t_ph;

int					current_time(void);
int					start(t_ph **ph);
void				my_usleep(int msec);
char				*get_message(int message);
int					clean(t_ph **ph, int status);
int					my_atoi(char *str, int *res);
int					ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

#endif
