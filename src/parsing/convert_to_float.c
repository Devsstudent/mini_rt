/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_float.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:36:53 by odessein          #+#    #+#             */
/*   Updated: 2022/11/30 15:23:19 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	convert_to_float(float *val, char *arr)
{
	int		i;
	int		j;
	int		dot;
	char	*nb;

	i = 0;
	j = 0;
	dot = 0;
	nb = malloc(sizeof(char) * (ft_strlen(arr) + 1));
	if (!nb)
	{
		//msg_error
		return (false);
	}
	while (arr[i])
	{
		if (arr[i] == '.')
		{
			dot = 1;
			if (arr[i + 1] && arr[i + 2] != '\0')
				dot++;
			i++;
			continue ;
		}
		nb[j] = arr[i];
		j++;
		i++;
	}
	nb[j] = '\0';
	if (dot == 1)
		*val = (float)(ft_atoi(nb)) / 10.0;
	else if (dot == 2)
		*val = (float)(ft_atoi(nb)) / 100.0;
	else
		*val = ft_atoi(nb);
	return (free(nb), true);
}
