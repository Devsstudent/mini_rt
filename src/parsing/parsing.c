/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:44:55 by odessein          #+#    #+#             */
/*   Updated: 2022/11/30 14:51:13 by odessein         ###   ########.fr       */
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
	{
		error_msg("Error\nNeed to have the extension .rt\n");
		return (false);
	}
}

bool	parsing(int ac, char **av)
{
	int		i;
	char	**lines;

	i = 0;
	lines = NULL;
	if (ac != 2)
		return (false);
	if (!check_extension(av[1]))
		return (false);
	if (!open_and_store(av[1], lines))
		return (false);
	return (true);
}
