/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:26:25 by odessein          #+#    #+#             */
/*   Updated: 2022/11/29 18:28:18 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	check_element_line(char **lines)
{
	int			i;
	t_must_have	all_elem;

	i = 0;
	init_all_elem(&all_elem);
	while (lines[i])
	{
		//split_line
		//checker la lettre corespondante en line_split[0]
		//en fonction exectuer la function (bool)
		//Si ok continuer
		//pour les "L" et "l" etc deux function ou pas ?
		//Si "L" set a value not possible to have "l"
		//onlyone case
	}
	if (!check_all_elem(all_elem))
		return (false);
	return (true);
}
