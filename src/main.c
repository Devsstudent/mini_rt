/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:50:57 by odessein          #+#    #+#             */
/*   Updated: 2022/11/30 19:46:35 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int		main(int ac, char **av)
{
	(void) av;
	//Structure definir sur la stack
	if (!parsing(ac, av))
		return (false);
	//Parsing
		//if not error msg (function for it)
	//Start_game
	return (0);
}

