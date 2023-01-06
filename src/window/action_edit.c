/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:20:50 by odessein          #+#    #+#             */
/*   Updated: 2023/01/06 17:23:07 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "edit.h"

static t_xyz	get_input_coord(void)
{
	t_xyz	res;
	long	x;
	long	y;
	long	z;

	x = get_input_nb("Enter the new x coordinate value\n");
	while (x > (long) INT_MAX)
		x = get_input_nb("Enter the new x coordinate value\n");
	y = get_input_nb("Enter the new y coordinate value\n");
	while (y > (long) INT_MAX)
		y = get_input_nb("Enter the new y coordinate value\n");
	z = get_input_nb("Enter the new z coordinate value\n");
	while (z > (long) INT_MAX)
		z = get_input_nb("Enter the new z coordinate value\n");
	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

static void	resize(t_edit *res, t_type type)
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
	else if (type == CY)
	{
		while (val <= 0 || val > INT_MAX || val > 2)
			val = get_input_nb("Enter 1 if you want to modify height otherwise enter 2\n");
		if (val == 1)
		{
			val = get_input_nb("Enter the new height :\n");
			while (val <= 0 || val > INT_MAX)
				val = get_input_nb("Enter the new height :\n");
			res->height = val;
		}
		else
		{
			res->action = RESIZE_WIDTH;
			val = get_input_nb("Enter the new width :\n");
			while (val <= 0 || val > INT_MAX)
				val = get_input_nb("Enter the new width :\n");
			res->width = val;
		}
	}
}

static int	get_angle_rotate(void)
{
	long	val;

	val = 400;
	while (val > 360 || val < -360)
		val = get_input_nb("Enter the angle of rotation you want: \n");
	return (val);
}

static bool	check_edit(t_type type, char *str)
{
	if (!str)
		return (false);
	if (*str == 'r' && (type == SP || type == CY))
		return (true);
	if (*str == 'o' && (type != LI && type != SP))
		return (true);
	if (*str == 't')
		return (true);
	return (false);
}

t_edit	get_edit(t_type type)
{
	char	*str;
	t_edit	res;

	res.action = UNDEF;
	res.coord.x = 0;
	res.coord.y = 0;
	res.coord.z = 0;
	res.width = 0;
	res.height = 0;
	res.diameter = 0;
	res.angle = 0;
	str = 0;
	while (!check_edit(type, str))
	{
		if (str)
			free(str);
		str = take_input_str("What kind of edit you want to apply ?\nr to resize\no to rotate\nt to translate\n");
	}
	if (*str == 'r')
		resize(&res, type);
	else if (*str == 'o')
	{
		res.action = ROTATE;
		res.angle = get_angle_rotate();
	}
	else if (*str == 't')
	{
		res.action = TRANSLATE;
		res.coord = get_input_coord();
	}
	return (res);
}
