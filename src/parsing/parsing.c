/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:44:55 by odessein          #+#    #+#             */
/*   Updated: 2022/11/24 11:19:15 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static bool	check_extension(char *name)
{
	int	i;

	i = 0;
	while (name[i])
		i++;
	if (i >= 4 && name[i - 1] == 't' && name[i - 2] == 'r' && name[i - 3] == '.')
		return (true);
	else
		return (false);
}

bool	parsing(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 2)
		return (false);
	if (!check_extension(av[1]))
		return (false);
	return (true);
}
