#include <philo.h>

long long	ft_atoi(const char *str)
{
	unsigned long long	num;
	int					sign;
	int					i;

	i = 0;
	num = 0;
	sign = 1;
	while (str[i] == '\n'
		|| str[i] == '\t'
		|| str[i] == '\r'
		|| str[i] == '\v'
		|| str[i] == '\f'
		|| str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		num = num * 10 + str[i++] - '0';
	return (num * sign);
}

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
		ph[i]->lf = i;
		ph[i]->rf = (i + 1) % ph[i]->d_tab->nb_philo;
		i++;
	}
	return (ph);
}

pthread_mutex_t *init_forks(t_game *d_tab)
{
    pthread_mutex_t	*forks;
	int				i;

	i = 0;
	if (d_tab->nb_philo > INTOFLOW || d_tab->t_t_die > LOFLOW
		|| d_tab->t_t_eat > LOFLOW || d_tab->t_t_sleep > LOFLOW
		|| d_tab->must_eat_nb > LOFLOW)
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

t_tab	init_table(char **argv, int ac)
{
    t_game   *d_tab;

    d_tab = (t_game *) malloc(sizeof(t_game) * 1);
	if ((ac == 5 || ac == 6) && alphanumeric(argv, 0, 1))
	{
		d_tab->nb_philo = ft_atoi(argv[1]);
		d_tab->t_t_die = ft_atoi(argv[2]);
		d_tab->t_t_eat = ft_atoi(argv[3]);
		d_tab->t_t_sleep = ft_atoi(argv[4]);
		if (ac == 6)
			d_tab->must_eat_nb = ft_atoi(argv[5]);
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
	return (NULL);
}

long long	get_current_time(void)
{
	struct timeval	te;
	long long		ms;

	gettimeofday(&te, NULL);
	ms = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (ms);
}

void	print_status(t_tab *d_tab, int id, char *s)
{
	pthread_mutex_lock(&d_tab->out_msg);
	printf("%lld %d %s", get_current_time() - d_tab->start_time, id + 1, s);
	if (s[0] != 'd')
		pthread_mutex_unlock(&d_tab->out_msg);
}

void eat_ph(t_philo *ph)
{
    pthread_mutex_lock(&ph->d_tab->forks[ph->lf]);
    print_status(ph->d_tab, ph->id, "has taken the left fork\n");
    pthread_mutex_lock(&ph->d_tab->forks[ph->rf]);
    print_status(ph->d_tab, ph->id, "has taken the right fork\n");
    pthread_mutex_lock(&ph->eating);
    print_status(ph->d_tab, ph->id, "is eating\n");
    ph->last_meal = get_current_time();
    ph->is_eating = 1; // initialize to 0;
    usleep(ph->d_tab->timetoeat * 1000 - 16000);
    while (get_current_time() - ph->last_meal < ph->d_tab->timetoeat)
        continue ;
    ph->number_times_ate++;
    ph->is_eating = 0; // when finished eating after time to eat reset to 0;
    pthread_mutex_unlock(&ph->eating);
    pthread_mutex_unlock(&ph->d_tab->forks[ph->lf]);
    pthread_mutex_unlock(&ph->d_tab->forks[ph->rf]);
}

void sleep_ph(t_philo *ph)
{
    long long time;

    print_status(ph->d_tab, ph->id, "is sleeping\n");
    time = get_current_time();
    usleep(philo->d_tab->t_t_sleep * 1000 - 16000);
    while (get_current_time() - time < ph->d_tab->t_t_sleep)
        continue ;
    return ;
}

void think_ph(t_philo *ph)
{
    print_status(philo->d_tab, ph->id, "is thinking\n");
    return ;
}

void routines(void *data)
{
    t_philo ph;

    ph = (t_philo *)data;
    while (ph->d_tab->death)
    {
        eat_ph(ph);
        sleep_ph(ph);
        think_ph(ph);
        usleep(100);
    }
    // return (NULL);
}

void    death_checker(void *data)
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

int start_threads(t_game *d_tab)
{
    int i;

    i = -1;
    d_tab->start_time = get_current_time();
    while (i++ < d_tab->nb_philo)
    {
        d_tab->ph[i]->last_time_ate = get_current_time();
		if (pthread_create(&d_tab->ph[i]->thread_id, NULL,
			&routines, (void *)d_tab->ph[i]) != 0)
			return (ERROR);
		usleep(100);
    }
    i = -1;
    while (i++ < d_tab->nb_philo)
    {
		if (pthread_create(&d_tab->ph[i]->thread_id, NULL,
			&death_checker, (void *)d_tab->ph[i]) != 0)
			return (ERROR);
		usleep(100);
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
        write(write(2, "Error: Invalid Argument\n", 23);
		return (0);
    }
    if (start_threads(d_tab) != 1)
        return (0);
    return (0);
}