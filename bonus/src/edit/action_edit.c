/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:20:50 by odessein          #+#    #+#             */
/*   Updated: 2023/02/05 23:32:22 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "edit.h"

static t_xyz	get_input_coord(t_edit *edit_info, bool *exit_request)
{
	t_xyz	res;
	float	x;
	float	y;
	float	z;

	ft_memset(&res, 0, sizeof(res));
	edit_info->action = TRANSLATE;
	x = get_input_nb("🔵 Enter the new x coordinate value\n", exit_request);
	if (*exit_request == true)
		return (res);
	y = get_input_nb("🔵 Enter the new y coordinate value\n", exit_request);
	if (*exit_request == true)
		return (res);
	z = get_input_nb("🔵 Enter the new z coordinate value\n", exit_request);
	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
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

static void	get_r_o_t(t_type type, char *str, t_edit *res, bool *exit_request)
{
	if (*str == 'r')
	{
		resize(res, type, exit_request);
		if (*exit_request == true)
			return (free(str));
	}
	else if (*str == 'o')
	{
		get_angle_rotate(res, exit_request);
		if (*exit_request == true)
			return (free(str));
	}
	else if (*str == 't')
		res->coord = get_input_coord(res, exit_request);
	return (free(str));
}

t_edit	get_edit(t_type type, bool *exit_request)
{
	char	*str;
	t_edit	res;

	ft_memset(&res, 0, sizeof(res));
	str = 0;
	while (!check_edit(type, str))
	{
		free(str);
		ft_putstr_fd("🔘 What kind of edit do you want to apply ?\n", 1);
		str = take_input_str("◽️r to resize\n◽️o to rotate\n◽️t to \
translate\n");
		if (str && ft_strncmp(str, "exit\n", 5) == 0)
			return (free(str), str = NULL, *exit_request = true, res);
	}
	get_r_o_t(type, str, &res, exit_request);
	return (res);
}
