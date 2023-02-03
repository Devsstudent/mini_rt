/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:37:27 by odessein          #+#    #+#             */
/*   Updated: 2023/01/10 15:49:14 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "edit.h"

static void	resize_cy(t_edit *res, long *val)
{
	while (*val <= 0 || *val > INT_MAX || *val > 2)
	{
		ft_putstr_fd("Enter 1 if you want to modify height", 1);
		*val = get_input_nb(" otherwise enter 2\n");
	}
	if (*val == 1)
	{
		*val = get_input_nb("Enter the new height :\n");
		while (*val <= 0 || *val > INT_MAX)
			*val = get_input_nb("Enter the new height :\n");
		res->height = *val;
	}
	else
	{
		res->action = RESIZE_WIDTH;
		*val = get_input_nb("Enter the new width :\n");
		while (*val <= 0 || *val > INT_MAX)
			*val = get_input_nb("Enter the new width :\n");
		res->width = *val;
	}
}

static void	resize_co(t_edit *res, long *val)
{
	while (*val <= 0 || *val > INT_MAX || *val > 2)
	{
		ft_putstr_fd("Enter 1 if you want to modify height", 1);
		*val = get_input_nb(" otherwise enter 2\n");
	}
	if (*val == 1)
	{
		*val = get_input_nb("Enter the new height :\n");
		while (*val <= 0 || *val > INT_MAX)
			*val = get_input_nb("Enter the new height :\n");
		res->height = *val;
	}
	else
	{
		res->action = RESIZE_WIDTH;
		*val = get_input_nb("Enter the new radius :\n");
		while (*val <= 0 || *val > INT_MAX)
			*val = get_input_nb("Enter the new radius :\n");
		res->width = *val;
	}
}

void	resize(t_edit *res, t_type type)
{
	long	val;

	res->action = RESIZE;
	val = 0;
	if (type == SP)
	{
		while (val <= 0 || val > INT_MAX)
			val = get_input_nb("Enter the new diameter of the sphere : \n");
		res->diameter = val;
	}
	else if (type == CY )
		resize_cy(res, &val);
	else if (type == CO)
		resize_co(res, &val);
}
