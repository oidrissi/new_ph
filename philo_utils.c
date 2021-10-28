/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 21:10:51 by oidrissi          #+#    #+#             */
/*   Updated: 2021/10/28 21:12:55 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	is_correct(char *str)
{
	int		i;

	i = 0;
	if ((str[0] == '-' || str[0] == '+') && str[1] == '\0')
		return (0);
	if (str[0] == '-' || str[0] == '+')
		str++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	correct_input(char **tab, t_data *data)
{
	int		i;

	i = 1;
	while (tab[i])
	{
		if (is_correct(tab[i]) == 0)
			ft_puterror("Error\n", &data);
		i++;
	}
	return (1);
}

long long	get_current_time(void)
{
	struct timeval	te;
	long long		ms;

	gettimeofday(&te, NULL);
	ms = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (ms);
}