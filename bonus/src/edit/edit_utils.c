/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:20:00 by odessein          #+#    #+#             */
/*   Updated: 2023/01/24 19:30:56 by odessein         ###   ########.fr       */
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

long	get_input_nb(char *ask)
{
	char	*str;
	long	nb;

	nb = (long) INT_MAX + 1;
	while (nb > INT_MAX)
	{
		str = take_input_str(ask);
		if (!str)
		{
			free(str);
			continue ;
		}
		if (str && ft_strlen(str) > 2 && !ft_is_digit(str[ft_strlen(str) - 2]))
			continue ;
		nb = ft_atoi(str);
	}
	return (nb);
}
