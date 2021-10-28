/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 21:16:43 by oidrissi          #+#    #+#             */
/*   Updated: 2021/10/28 21:16:50 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *death_checker(void *data)
{
    t_philo *ph;

    ph = (t_philo *)data;
    while (ph->d_tab->death)
    {
        if (!ph->is_eating
			&& get_current_time() - ph->last_time_ate >= ph->d_tab->t_t_die)
		{
			pthread_mutex_lock(&ph->eating);
			print_status(ph->d_tab, ph->id, "died\n");
			ph->d_tab->death = 0;
			pthread_mutex_unlock(&ph->eating);
		}
		if (ph->d_tab->ph[ph->d_tab->nb_philo - 1]->number_times_ate
			== ph->d_tab->must_eat_nb)
			ph->d_tab->death = 0;
		usleep(100);
    }
	return (NULL);
}