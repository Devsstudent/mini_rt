/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:57:53 by odessein          #+#    #+#             */
/*   Updated: 2022/11/29 16:11:24 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "minirt.h"
#include "parsing.h"

bool	free_split_return_false(char **line_split)
{
	int	i;

	i = 0;
	while (line_split[i])
	{
		free(line_split[i]);
		i++;
	}
	free(line_split[i]);
	return (false);
}

bool	ft_is_space(char c)
{
	if (c < 15 && c > 6)
		return (true);
	if (c == 32)
		return (true);
	return (false);
}
