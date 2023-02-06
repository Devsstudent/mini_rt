/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:20:00 by odessein          #+#    #+#             */
/*   Updated: 2023/02/05 21:22:11 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "edit.h"

char	*take_input_str(char *str)
{
	char	*res;

	ft_putstr_fd(str, 1);
	res = get_next_line(0);
	return (res);
}

static bool	check_after_dot(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_digit(str[i]) || i > 2)
		{
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	check_nb(char *str, float *nb)
{
	int		i;

	i = 0;
	if (!str)
		return (false);
	if ((str[0] == '+' || str[0] == '-') && str[1])
		i++;
	while (str[i] && str[i] != '.')
	{
		if (!ft_is_digit(str[i++]))
			return (false);
	}
	if ((ft_is_digit(str[0]) && i > 10) || (!ft_is_digit(str[0]) && i > 11))
		return (false);
	if (str[i])
	{
		i++;
		if (!check_after_dot(str + i))
			return (false);
	}
	convert_to_float(nb, str);
	if (*nb == (float)21474836489 || *nb == (float)214783648.9
		|| *nb == (float)21478364.89)
		return (false);
	return (true);
}

float	get_input_nb(char *ask, bool *exit_request)
{
	char	*str;
	float	nb;

	str = take_input_str(ask);
	str[ft_strlen(str) - 1] = '\0';
	if (str && ft_strncmp(str, "exit", 5) == 0)
		return (free(str), str = NULL, *exit_request = true, 0);
	while (!check_nb(str, &nb))
	{
		free(str);
		str = take_input_str(ask);
		str[ft_strlen(str) - 1] = '\0';
		if (!str)
			continue ;
		if (str && ft_strncmp(str, "exit", 5) == 0)
			return (free(str), str = NULL, *exit_request = true, 0);
	}
	free(str);
	return (nb);
}

long	get_input_nb_int(char *ask, bool *exit_request)
{
	char	*str;
	long	nb;

	nb = (long) INT_MAX + 1;
	while (nb > INT_MAX)
	{
		str = take_input_str(ask);
		if (str && ft_strncmp(str, "exit\n", 5) == 0)
			return (free(str), str = NULL, *exit_request = true, 0);
		if (!str)
			continue ;
		if (str && (!ft_strncmp(str, "-\n", 3) || !ft_strncmp(str, "+\n", 3)
				|| (ft_strlen(str) > 2
					&& !ft_is_digit(str[ft_strlen(str) - 2]))))
			continue ;
		if (str && ft_strncmp(str, "exit\n", 5) == 0)
			return (free(str), str = NULL, *exit_request = true, 0);
		nb = ft_atoi(str);
		free(str);
	}
	return (nb);
}
