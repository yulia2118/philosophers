/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:37:12 by fdarrin           #+#    #+#             */
/*   Updated: 2021/04/10 15:33:03 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <pthread.h>
# include <signal.h>
# include <semaphore.h>
# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DEAD 5
# define ERR_ARGS -2
# define ERR_TIME -3
# define ERR_MALLOC -4

typedef struct s_info
{
	sem_t			*forks;
	sem_t			*semaphor;
	sem_t			*print_sem;
	sem_t			*print_dead_sem;
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
	pthread_t		check_thread;
	pid_t			pid;
	t_info			*info;
	int				last_meal;
	int				meals;
	int				number;
}					t_ph;

int					current_time(void);
int					start(t_ph **ph);
void				my_usleep(int msec);
char				*get_message(int message);
void				ph_kill(t_ph **ph);
int					clean(t_ph **ph, int status);
int					my_atoi(char *str, int *res);
int					ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

#endif
