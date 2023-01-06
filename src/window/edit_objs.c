/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:38:20 by odessein          #+#    #+#             */
/*   Updated: 2023/01/06 13:58:35 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

char	*take_input_str(char *str)
{
	char	*res;

	ft_putstr_fd(str, 1);
	res = get_next_line(0);
	return (res);
}

long	get_input_nb(char *ask)
{
	char	*str;
	long	nb;

	nb = 0;
	while (nb > INT_MAX || nb <= 0)
	{
		str = take_input_str(ask);
		nb = ft_atoi(str);
		free(str);
	}
	return (nb);
}

bool	check_edit(t_type type, char *str)
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

t_xyz	get_input_coord(void)
{
	t_xyz	res;

	res.x = get_input_nb("Enter the new x coordinate value\n");
	while ((long) res.x > INT_MAX)
		res.x = get_input_nb("Enter the new x coordinate value\n");
	res.y = get_input_nb("Enter the new y coordinate value\n");
	while ((long) res.y > INT_MAX)
		res.y = get_input_nb("Enter the new y coordinate value\n");
	res.z = get_input_nb("Enter the new z coordinate value\n");
	while ((long) res.z > INT_MAX)
		res.z = get_input_nb("Enter the new z coordinate value\n");
	return (res);
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
	else if (type == CY)
	{
		while (val <= 0 || val > INT_MAX || val > 2)
			val = get_input_nb("Enter 1 if you want to modify height otherwise enter 2\n");
		if (val == 1)
		{
			while (val <= 0 || val > INT_MAX)
				val = get_input_nb("Enter the new height :\n");
			res->height = val;
		}
		else
		{
			while (val <= 0 || val > INT_MAX)
				val = get_input_nb("Enter the new width :\n");
			res->width = val;
		}
	}
}

int	get_angle_rotate(void)
{
	long	val;

	val = 400;
	while (val > 360 || val < -360)
		val = get_input_nb("Enter the angle of rotation you want: \n");
	return (val);
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
	res.angle = 500;
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

bool	ask_sp(t_objects *objs)
{
	t_type		type;
	long		nb;
	char		*buff;
	//t_sphere	*sp;
	t_edit		edit_info;

	type = SP;
	nb = 0;
	while (nb > INT_MAX || nb > objs->nb_sp || nb <= 0)
	{
		buff = take_input_str("Which sphere do you want to select ?\n");
		nb = atoi(buff);
		free(buff);
	}
	edit_info = get_edit(type);
	(void) edit_info;
//	apply_action_sp(edit_info, &objs->sp[nb]);
	return (true);
}

bool	ask_cy(t_objects *objs)
{
	t_type	type;
	long	nb;
	char	*buff;
	t_edit		edit_info;

	type = CY;
	nb = 0;
	while (nb > INT_MAX || nb > objs->nb_cy || nb <= 0)
	{
		buff = take_input_str("Which cylinder do you want to select ?\n");
		nb = atoi(buff);
		free(buff);
	}
	edit_info = get_edit(type);
	(void) edit_info;
	return (true);
}

bool	ask_pl(t_objects *objs)
{
	t_type	type;
	long	nb;
	char	*buff;
	t_edit		edit_info;

	nb = 0;
	type = PL;
	while (nb > INT_MAX || nb > objs->nb_pl || nb <= 0)
	{
		buff = take_input_str("Which plane do you want to select ?\n");
		nb = atoi(buff);
		free(buff);
	}
	edit_info = get_edit(type);
	(void) edit_info;
	return (true);
}

bool	ask_li(t_objects *objs)
{
	t_type	type;
	long	nb;
	char	*buff;
	t_edit		edit_info;

	type = LI;
	nb = 0;
	while (nb > INT_MAX || nb > objs->nb_li || nb <= 0)
	{
		buff = take_input_str("Which light do you want to select ?\n");
		nb = atoi(buff);
		free(buff);
	}
	edit_info = get_edit(type);
	(void) edit_info;
	return (true);
}

bool	ask_c(t_objects *objs)
{
	t_edit		edit_info;
	t_type	type;

	type = C;
	edit_info = get_edit(type);
	(void) objs;
	(void) edit_info;
	return (true);
}

bool	check_str(char *str)
{

	if (!str)
	       return (false);
	else if (!ft_strncmp("sp", str, 3))
	       return (true);
	else if (!ft_strncmp("cy", str, 3))
	       return (true);
	else if (!ft_strncmp("pl", str, 3))
	       return (true);
	else if (!ft_strncmp("li", str, 3))
	       return (true);
	else if (!ft_strncmp("c", str, 2))
	       return (true);
	return (false);
}

void	go_for_asked(char *str, t_objects *objs)
{
	if (!str)
		return ;
	if (!ft_strncmp("sp", str, 3))
		ask_sp(objs);
	if (!ft_strncmp("cy", str, 3))
		ask_cy(objs);
	if (!ft_strncmp("pl", str, 3))
		ask_pl(objs);
	if (!ft_strncmp("li", str, 3))
		ask_li(objs);
	if (!ft_strncmp("c", str, 2))
		ask_c(objs);
	free(str);
}

void	edit_objs(t_objects *objs)
{
	char	*str;

	str = 0;
	while (!check_str(str))
	{
		if (str)
			free(str);
		str = take_input_str("Which object type you want to edit ?\n");
	}
	go_for_asked(str, objs);
}



/*
void	apply_action_sp(t_edit edit_info, t_sphere *sp)
{
	if (edit_info.action == RESIZE)
	{

	}
	else if (edit_info.action == ROTATE)
	{

	}
	else if (edit_info.action == TRANSLATE)
	{

	}
}
*/
