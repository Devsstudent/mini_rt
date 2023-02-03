/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:20:50 by odessein          #+#    #+#             */
/*   Updated: 2023/01/28 19:30:42 by mbelrhaz         ###   ########.fr       */
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

void	get_angle_rotate(t_edit *edit_info)
{
	long	val;
	char	*buff;

	val = 400;
	edit_info->action = ROTATE;
	buff = 0;
	while (val > 360 || val < -360)
		val = get_input_nb("Enter the angle of rotation you want: \n");
	while (!buff || (ft_strncmp("x\n", buff, 3)
			&& ft_strncmp("y\n", buff, 3)
			&& ft_strncmp("z\n", buff, 3)))
	{
		if (buff)
			free(buff);
		buff = take_input_str("Over which axis do you want to rotate \n");
	}
	if (!ft_strncmp("x\n", buff, 3))
		edit_info->axis = X;
	else if (!ft_strncmp("y\n", buff, 3))
		edit_info->axis = Y;
	else if (!ft_strncmp("z\n", buff, 3))
		edit_info->axis = Z;
	free(buff);
	edit_info->angle = val;
}

static bool	check_edit(t_type type, char *str)
{
	if (!str)
		return (false);
	if (!ft_strncmp("r\n", str, 3) && (type == SP || type == CY || type == CO))
		return (true);
	if (!ft_strncmp("o\n", str, 3) && type != LI)
		return (true);
	if (!ft_strncmp("t\n", str, 3))
		return (true);
	return (false);
}

t_edit	get_edit(t_type type)
{
	char	*str;
	t_edit	res;

	ft_memset(&res, 0, sizeof(res));
	str = 0;
	while (!check_edit(type, str))
	{
		if (str)
			free(str);
		ft_putstr_fd("What kind of edit you want to apply ?\n", 1);
		str = take_input_str("r to resize\no to rotate\nt to translate\n");
	}
	if (*str == 'r')
		resize(&res, type);
	else if (*str == 'o')
		get_angle_rotate(&res);
	else if (*str == 't')
	{
		res.action = TRANSLATE;
		res.coord = get_input_coord();
	}
	free(str);
	return (res);
}
