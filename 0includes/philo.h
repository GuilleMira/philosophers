/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:48:40 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/09 13:39:27 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* LIBS */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
/* PROGRAM OPTIONS */
# define OPT_1	5
# define OPT_2	6
# define CONVER	1000000
# define LEFT	0
# define RIGHT	1
# define MINPHI	1
/* ERROR MESSAGES */
# define EX		"Error.\n"
/* MESSAGES */
# define KNIFE	"(%i) Philo %i has taken a fork 🗡\n"
# define EAT	"(%i) Philo %i is eating\n"
# define SLEEP	"(%i) Philo %i is sleeping\n"
# define THINK	"(%i) Philo %i is thinking\n"
# define DIED	"(%i) Philo %i died\n"

typedef int	t_bool;

/** Struct that stores single direction linked list. */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/** Struct of a vector, 2D representation. */
typedef struct s_vector
{
	int	x;
	int	y;
}		t_vector;

/** Struct that stores argument times. */
typedef struct s_times
{
	int				total_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_eat;
	int				in_execution;
	struct timeval	init_time;
}		t_time;

/** Struct that stores philospher variables. */
typedef struct s_philo
{
	int				index;
	int				time_ate;
	int				complete;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*print;
	pthread_mutex_t	*dead;
	pthread_t		thread;
	t_time			*times;
}				t_philo;

/* PARSER AND ARGUMENTS */
int				parser(int argc, char *argv[]);
/* ARGUMENT READ */
t_time			*reader(int argc, char *argv[]);
/* PHILOSPHERS MANAGEMENT */
int				get_miliseconds(struct timeval	init_time);
int				create_philos(t_philo **array, int total_philos);
pthread_mutex_t	**create_mutex(int total_philos);
int				assign_mutex(t_time *arg, \
int total_philos, pthread_mutex_t	*knives);
void			acc_sleep(int time, struct timeval init);
/* PHILOSPHERS ROUTINE */
int				create_threads(t_philo **array, int total_philos);
/* PHILOSPHERS LINKER */
void			link_philos_and_mutex(t_philo **array, \
pthread_mutex_t **knives, int total_philos);
int				init_philos(t_philo **array, t_time *arg);
/* MEMORY MANAGEMENT */
void			ft_shutdown(t_time *arg);
void			clean_argument(t_time *arg);
void			free_array_philos(t_philo **array, int total_philos);
void			free_array_mutex(pthread_mutex_t **array, int total_philos);
void			mutex_destructor(pthread_mutex_t **knives, int total_philos);
void			clean_simulation(t_philo **array, \
pthread_mutex_t **knives, int total_philos);
/* ACTIONS */
void			knife(t_philo *philo);
void			eat(t_philo *philo);
void			ft_sleep(t_philo *philo);
void			think(t_philo *philo);
/* ACTIONS SECOND*/
void			release_knife(t_philo *philo, int flag);
void			grab_knife(t_philo *philo, int flag);
void			dead_message(t_philo *philo);
/* DEATH_CONTROL */
int				dead_checker(t_philo **array, int total_philos);
void			single_dead_message(t_philo *philo);
int				augmented_dead_checker(t_philo **array, int total_philos);
/* TOOLKIT */
int				ft_isspaces(int c);
void			*ft_calloc(size_t count, size_t size);
t_bool			ft_isdigit(int c);
int				ft_atoi(const char *str);
#endif
