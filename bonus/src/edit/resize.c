/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:37:27 by odessein          #+#    #+#             */
/*   Updated: 2023/02/05 21:11:40 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "edit.h"

static bool	modify_height(t_edit *res, float *val, bool *exit_request)
{
	*val = get_input_nb("Enter the new height :\n", exit_request);
	if (*exit_request == true)
		return (false);
	while (*val <= 0 || *val > (float)INT_MAX)
	{
		*val = get_input_nb("Enter the new height :\n", exit_request);
		if (*exit_request == true)
			return (false);
	}
	res->height = *val;
	return (true);
}

static void	resize_cy(t_edit *res, float *val, bool *exit_request)
{
	while (*val <= 0 || *val > (float)INT_MAX || *val > 2)
	{
		*val = get_input_nb_int("Enter 1 if you want to modify\
height otherwise enter 2\n", exit_request);
		if (*exit_request == true)
			return ;
	}
	if (*val == 1)
	{
		if (!modify_height(res, val, exit_request))
			return ;
	}
	else
	{
		res->action = RESIZE_WIDTH;
		*val = get_input_nb("Enter the new width :\n", exit_request);
		if (*exit_request == true)
			return ;
		while (*val <= 0 || *val > (float)INT_MAX)
		{
			*val = get_input_nb("Enter the new width :\n", exit_request);
			if (*exit_request == true)
				return ;
		}
		res->width = *val;
	}
}

static void	resize_co(t_edit *res, float *val, bool *exit_request)
{
	while (*val <= 0 || *val > (float)INT_MAX || *val > 2)
	{
		*val = get_input_nb_int("Enter 1 if you want to modify\
height otherwise enter 2\n", exit_request);
		if (*exit_request == true)
			return ;
	}
	if (*val == 1)
	{
		if (!modify_height(res, val, exit_request))
			return ;
	}
	else
	{
		res->action = RESIZE_WIDTH;
		*val = get_input_nb("Enter the new radius :\n", exit_request);
		if (*exit_request == true)
			return ;
		while (*val <= 0 || *val > (float)INT_MAX)
		{
			*val = get_input_nb("Enter the new radius :\n", exit_request);
			if (*exit_request == true)
				return ;
		}
		res->width = *val;
	}
}

void	resize(t_edit *res, t_type type, bool *exit_request)
{
	float	val;

	res->action = RESIZE;
	val = 0;
	if (type == SP)
	{
		while (val <= 0)
		{
			val = get_input_nb("Enter the new diameter of the sphere : \n",
					exit_request);
			if (*exit_request == true)
				return ;
		}
		res->diameter = val;
	}
	else if (type == CY)
	{
		resize_cy(res, &val, exit_request);
		if (*exit_request == true)
			return ;
	}
	else if (type == CO)
		resize_co(res, &val, exit_request);
}
