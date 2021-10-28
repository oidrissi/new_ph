/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 20:45:28 by oidrissi          #+#    #+#             */
/*   Updated: 2021/10/28 20:45:28 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo **init_philo(t_game *d_tab)
{
    t_philo	**ph;
	int		i;

	i = 0;
	ph = (t_philo **)malloc(sizeof(t_philo *) * d_tab->nb_philo + 1);
	if (ph == NULL)
		return (NULL);
	while (i < d_tab->nb_philo)
	{
		ph[i] = (t_philo *)malloc(sizeof(t_philo) * 1);
		if (ph[i] == NULL)
			return (NULL);
		if (pthread_mutex_init(&ph[i]->eating, 0) != 0)
			return (NULL);
		ph[i]->d_tab = d_tab;
		ph[i]->id = i;
		ph[i]->is_eating = 0;
		ph[i]->number_times_ate = 0;
		ph[i]->l_fork = i;
		ph[i]->r_fork = (i + 1) % ph[i]->d_tab->nb_philo;
		i++;
	}
	return (ph);
}

pthread_mutex_t *init_forks(t_game *d_tab)
{
    pthread_mutex_t	*forks;
	int				i;

	i = 0;
	if (d_tab->nb_philo > INTOFLOW || d_tab->t_t_die > INTOFLOW
		|| d_tab->t_t_eat > INTOFLOW || d_tab->t_t_sleep > INTOFLOW
		|| d_tab->must_eat_nb > INTOFLOW)
	{
		write(2, "Error: Invalid Argument\n", 23);
		return (NULL);
	}
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * d_tab->nb_philo);
	if (forks == NULL)
		return (NULL);
	while (i < d_tab->nb_philo)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (NULL);
		i++;
	}
	return (forks);
}

t_game	*init_table(int ac, char **av)
{
    t_game   *d_tab;

    d_tab = (t_game *) malloc(sizeof(t_game) * 1);
	if ((ac == 5 || ac == 6) && correct_input(av))
	{
		d_tab->nb_philo = ft_atoi(av[1]);
		d_tab->t_t_die = ft_atoi(av[2]);
		d_tab->t_t_eat = ft_atoi(av[3]);
		d_tab->t_t_sleep = ft_atoi(av[4]);
		d_tab->must_eat_nb = -1;
		if (ac == 6)
			d_tab->must_eat_nb = ft_atoi(av[5]);
		d_tab->death = 1;
		if (d_tab->nb_philo <= 0 || d_tab->t_t_die <= 0 || d_tab->t_t_eat <= 0
			|| d_tab->t_t_sleep <= 0)
			return (NULL);
        d_tab->forks = init_forks(d_tab);
        if (d_tab->forks == NULL)
		    return (NULL);
        d_tab->ph = init_philo(d_tab);
        if (d_tab->ph == NULL || d_tab->nb_philo == 0)
		    return (NULL);
        if (pthread_mutex_init(&d_tab->out_msg, 0) != 0)
		    return (NULL);
        return (d_tab);
	}
	return (d_tab);
}

int start_threads(t_game *d_tab)
{
    int i;

    i = 0;
    d_tab->start_time = get_current_time();
    while (i < d_tab->nb_philo)
    {
        d_tab->ph[i]->last_time_ate = get_current_time();
		if (pthread_create(&d_tab->ph[i]->thread_id, NULL,
			&routines, (void *)d_tab->ph[i]) != 0)
			return (0);
		i++;
		usleep(100);
    }
    i = 0;
    while (i < d_tab->nb_philo)
    {
		if (pthread_create(&d_tab->ph[i]->death_thread, NULL,
			&death_checker, (void *)d_tab->ph[i]) != 0)
			return (0);
		usleep(100);
		i++;
    }
    while (d_tab->death)
		continue ;
    return (1);
}

int main(int ac, char **av)
{
    t_game   *d_tab;

    d_tab = init_table(ac, av);
    if (d_tab == NULL)
    {
        write(2, "Error: Invalid Argument\n", 23);
		return (0);
    }
    if (start_threads(d_tab) != 1)
        return (0);
    return (0);
}