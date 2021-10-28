/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 20:45:37 by oidrissi          #+#    #+#             */
/*   Updated: 2021/10/28 20:45:37 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <stdio.h>		//	printf
# include <stdlib.h>	//	malloc
# include <string.h>	//	memset
# include <unistd.h>	//	usleep
# include <sys/time.h>	//	gettimeofday(struct timeval *restrict tv,
                    	//	struct timezone *restrict tz);
# include <pthread.h>	// 1 - int pthread_create(pthread_t *restrict thread, ------->  The pthread_create() function starts a new thread in the calling
       					//	process.  The new thread starts execution by invoking
       					//	start_routine(); arg is passed as the sole argument of
       					//	start_routine().
                    	//  const pthread_attr_t *restrict attr,
                        //  void *(*start_routine)(void *),
                        //  void *restrict arg);
						
						//	2 - int pthread_detach(pthread_t thread); detach a thread from process
						//	3 - pthread_join -->  The pthread_join() function waits for the thread specified by
       					//	thread to terminate.  If that thread has already terminated, then
						//	pthread_join() returns immediately.  The thread specified by
						//	thread must be joinable.
						//	4 - pthread_mutex_init --> pthread_mutex_init, pthread_mutex_destroy - initialise or destroy a mutex
						//	The pthread_mutex_init() function initialises the mutex referenced by mutex with attributes specified by attr. If attr is NULL,
						//	the default mutex attributes are used; the effect is the same as passing the address of a default mutex attributes object. Upon
						//	successful initialisation, the state of the mutex becomes initialised and unlocked.
						//	5 - int pthread_mutex_lock(pthread_mutex_t *mutex);
						//	6 - int pthread_mutex_unlock(pthread_mutex_t *mutex);

#define LOFLOW 9223372036854775807
#define INTOFLOW 2147483647

typedef	struct s_philo
{
	int					id;
	long long			last_time_ate;
	pthread_mutex_t		eating;
	pthread_t			thread_id;
	pthread_t			death_thread;
	int					l_fork;
    int					r_fork;
	unsigned int		number_times_ate;
	int					is_eating;
	int					done;
	char				*status;
	struct s_game		*d_tab;
	
}	t_philo;

typedef	struct	s_game
{
	pthread_mutex_t	out_msg;
    pthread_mutex_t	*forks;
	int				n_p;
	long long		start_time;
	long long		t_t_die;
	long long		t_t_sleep;
	long long		t_t_eat;
	long long		must_eat_nb;
	long long		death;
	t_philo         **ph;

}	t_game;

int 		main(int ac, char **av);
int			correct_input(char **tab);
long long	get_current_time(void);
void		print_status(t_game *d_tab, int id, char *s);
void 		*routines(void *data);
void    	*death_checker(void *data);
long long	ft_atoi(const char *str);

#endif