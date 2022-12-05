/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_structs_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 20:05:57 by mbelrhaz          #+#    #+#             */
/*   Updated: 2022/12/04 20:56:14 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_structs(t_objects *objects)
{
	free(objects->amb);
	free(objects->cam);
	free(objects->li);
	free(objects->sp);
	free(objects->pl);
	free(objects->cy);
}

void	free_double_arr(char **double_arr)
{
	int	i;

	i = 0;
	while (double_arr[i])
	{
		free(double_arr[i]);
		i++;
	}
	free(double_arr);
}

void	free_triple_arr(char ***triple_arr)
{
	int	i;

	i = 0;
	while (triple_arr[i])
	{
		free_double_arr(triple_arr[i]);
		i++;
	}
	free(triple_arr);
}
