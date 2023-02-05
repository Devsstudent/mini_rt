/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:38:20 by odessein          #+#    #+#             */
/*   Updated: 2023/02/04 20:17:44 by mbelrhaz         ###   ########.fr       */
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
	else if (!ft_strncmp("co\n", str, 4))
		return (true);
	return (false);
}

static bool	go_for_asked(char *str, t_objects *objs)
{
	bool	ret;

	ret = true;
	if (!str)
		return (false);
	if (!ft_strncmp("sp\n", str, 4))
		ret = ask_sp(objs);
	if (!ft_strncmp("cy\n", str, 4))
		ret = ask_cy(objs);
	if (!ft_strncmp("pl\n", str, 4))
		ret = ask_pl(objs);
	if (!ft_strncmp("li\n", str, 4))
		ret = ask_li(objs);
	if (!ft_strncmp("c\n", str, 3))
		ret = ask_c(objs);
	if (!ft_strncmp("co\n", str, 4))
		ret = ask_co(objs);
	free(str);
	return (ret);
}

void	edit_objs(t_objects *objs)
{
	char	*str;

	str = NULL;
	while (!check_str(str))
	{
		if (str)
			free(str);
		str = take_input_str("Which object type do you want to edit ?\n");
		if (str && ft_strncmp(str, "exit\n", 5) == 0)
		{
			free(str);
			str = NULL;
			return ;
		}
	}
	if (go_for_asked(str, objs))
		objs->need_display = true;
}
