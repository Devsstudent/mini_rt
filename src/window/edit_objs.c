/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:38:20 by odessein          #+#    #+#             */
/*   Updated: 2023/01/06 17:24:14 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"


static bool	check_str(char *str)
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

static void	go_for_asked(char *str, t_objects *objs)
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
//	objs->editing = true;
	while (!check_str(str))
	{
		if (str)
			free(str);
		str = take_input_str("Which object type you want to edit ?\n");
	}
	go_for_asked(str, objs);
	//objs->editing = false;
	objs->need_display = true;
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
