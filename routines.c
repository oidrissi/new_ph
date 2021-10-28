/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 21:13:42 by oidrissi          #+#    #+#             */
/*   Updated: 2021/10/28 21:14:45 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_game *d_tab, int id, char *s)
{
	pthread_mutex_lock(&d_tab->out_msg);
	printf("%lld %d %s", get_current_time() - d_tab->start_time, id + 1, s);
	if (s[0] != 'd')
		pthread_mutex_unlock(&d_tab->out_msg);
}

void eat_ph(t_philo *ph)
{
    pthread_mutex_lock(&ph->d_tab->forks[ph->l_fork]);
    print_status(ph->d_tab, ph->id, "has taken the left fork\n");
    pthread_mutex_lock(&ph->d_tab->forks[ph->r_fork]);
    print_status(ph->d_tab, ph->id, "has taken the right fork\n");
    pthread_mutex_lock(&ph->eating);
    print_status(ph->d_tab, ph->id, "is eating\n");
    ph->last_time_ate = get_current_time();
    ph->is_eating = 1; // initialize to 0;
    usleep(ph->d_tab->t_t_eat * 1000 - 16000);
    while (get_current_time() - ph->last_time_ate < ph->d_tab->t_t_eat)
        continue ;
    ph->number_times_ate++;
    ph->is_eating = 0; // when finished eating after time to eat reset to 0;
    pthread_mutex_unlock(&ph->eating);
    pthread_mutex_unlock(&ph->d_tab->forks[ph->l_fork]);
    pthread_mutex_unlock(&ph->d_tab->forks[ph->r_fork]);
}

void sleep_ph(t_philo *ph)
{
    long long time;

    print_status(ph->d_tab, ph->id, "is sleeping\n");
    time = get_current_time();
    usleep(ph->d_tab->t_t_sleep * 1000 - 16000);
    while (get_current_time() - time < ph->d_tab->t_t_sleep)
        continue ;
	return ;
}

void think_ph(t_philo *ph)
{
    print_status(ph->d_tab, ph->id, "is thinking\n");
	return ;
}

void *routines(void *data)
{
    t_philo *ph;

    ph = (t_philo *)data;
    while (ph->d_tab->death)
    {
        eat_ph(ph);
        sleep_ph(ph);
        think_ph(ph);
        usleep(100);
    }
    return (NULL);
}