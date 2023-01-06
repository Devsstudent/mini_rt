/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:38:20 by odessein          #+#    #+#             */
/*   Updated: 2023/01/06 15:49:24 by odessein         ###   ########.fr       */
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

	nb = (long) INT_MAX + 1;
	while (nb > INT_MAX)
	{
		str = take_input_str(ask);
		if (!str)
		{
			free(str);
			continue ;
		}
		nb = ft_atoi(str);
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
			val = get_input_nb("Enter the new height :\n");
			while (val <= 0 || val > INT_MAX)
				val = get_input_nb("Enter the new height :\n");
			res->height = val;
		}
		else
		{
			val = get_input_nb("Enter the new width :\n");
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

bool	ask_sp(t_objects *objs)
{
	t_type		type;
	long		nb;
	//t_sphere	*sp;
	t_edit		edit_info;

	type = SP;
	nb = 0;
	while (nb > INT_MAX || nb > objs->nb_sp || nb <= 0)
		nb = get_input_nb("Which sphere do you want to select ?\n");
	edit_info = get_edit(type);
	(void) edit_info;
//	apply_action_sp(edit_info, &objs->sp[nb]);
	return (true);
}

bool	ask_cy(t_objects *objs)
{
	t_type	type;
	long	nb;
	t_edit		edit_info;

	if (objs->nb_cy == 0)
	{
		//I guess i the end we should INVALID MAP if not 1 cylinder & 1 sphere & 1 plane
		ft_putstr_fd("No cylinder sorry :(\n", 1);
		return (true);
	}
	type = CY;
	nb = 0;
	while (nb > INT_MAX || nb > objs->nb_cy || nb <= 0)
		nb = get_input_nb("Which cylinder do you want to select ?\n");
	edit_info = get_edit(type);
	(void) edit_info;
	return (true);
}

bool	ask_pl(t_objects *objs)
{
	t_type	type;
	long	nb;
	t_edit		edit_info;

	nb = 0;
	type = PL;
	while (nb > INT_MAX || nb > objs->nb_pl || nb <= 0)
		nb = get_input_nb("Which plane do you want to select ?\n");
	edit_info = get_edit(type);
	(void) edit_info;
	return (true);
}

bool	ask_li(t_objects *objs)
{
	t_type	type;
	long	nb;
	t_edit		edit_info;

	type = LI;
	nb = 0;
	while (nb > INT_MAX || nb > objs->nb_li || nb <= 0)
		nb = get_input_nb("Which light do you want to select ?\n");
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
	if (!ft_strncmp("sp\n", str, 4))
	       return (true);
	else if (!ft_strncmp("cy\n", str, 4))
	       return (true);
	else if (!ft_strncmp("pl\n", str, 4))
	       return (true);
	else if (!ft_strncmp("li\n", str, 4))
	       return (true);
	else if (!ft_strncmp("c\n", str, 3))
	       return (true);
	return (false);
}

void	go_for_asked(char *str, t_objects *objs)
{
	if (!str)
		return ;
	if (!ft_strncmp("sp\n", str, 4))
		ask_sp(objs);
	if (!ft_strncmp("cy\n", str, 4))
		ask_cy(objs);
	if (!ft_strncmp("pl\n", str, 4))
		ask_pl(objs);
	if (!ft_strncmp("li\n", str, 4))
		ask_li(objs);
	if (!ft_strncmp("c\n", str, 3))
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
