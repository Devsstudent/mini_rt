/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:03:54 by odessein          #+#    #+#             */
/*   Updated: 2022/12/19 15:53:18 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	create_color(t_rgb rgb)
{
	int	color;

	color = 0;
	color = (color << 16 & rgb.R) | color;
	color = (color << 8 & rgb.G) | color;
	color = (color << 0 & rgb.B) | color;
	return (color);
}

void	add_color(int *color, t_rgb rgb)
{
	*color = (*color << 16 & ((*color << 16) / 2 + rgb.R / 2));
	*color = (*color << 8 & ((*color << 8) / 2 + rgb.G / 2));
	*color = (*color << 0 & ((*color << 0) / 2 + rgb.B / 2));
}
