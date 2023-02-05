/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rotation_angle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 20:58:25 by mbelrhaz          #+#    #+#             */
/*   Updated: 2023/02/05 21:02:50 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "edit.h"

static void	fill_axis(t_edit *edit_info, char *buff)
{
	if (!ft_strncmp("x\n", buff, 3))
		edit_info->axis = X;
	else if (!ft_strncmp("y\n", buff, 3))
		edit_info->axis = Y;
	else if (!ft_strncmp("z\n", buff, 3))
		edit_info->axis = Z;
}

void	get_angle_rotate(t_edit *edit_info, bool *exit_request)
{
	long	val;
	char	*buff;

	val = 400;
	edit_info->action = ROTATE;
	buff = 0;
	while (val > 360 || val < -360)
	{
		val = get_input_nb_int("Enter the angle of rotation you want: \n",
				exit_request);
		if (*exit_request == true)
			return ;
	}
	while (!buff || (ft_strncmp("x\n", buff, 3) && ft_strncmp("y\n", buff, 3)
			&& ft_strncmp("z\n", buff, 3)))
	{
		free(buff);
		buff = take_input_str("Over which axis do you want to rotate \n");
		if (buff && ft_strncmp(buff, "exit\n", 5) == 0)
			return (free(buff), buff = NULL, *exit_request = true, free(buff));
	}
	fill_axis(edit_info, buff);
	free(buff);
	edit_info->angle = val;
}
