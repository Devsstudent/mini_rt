/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:03:54 by odessein          #+#    #+#             */
/*   Updated: 2022/12/19 12:04:35 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	create_color(unsigned char r, unsigned char g, unsigned char b)
{
	int	color;

	color = 0;
	color = (color << 16 & r) | color;
	color = (color << 8 & g) | color;
	color = (color << 0 & b) | color;
	return (color);
}

void	add_color(int *color, unsigned char r, unsigned char g, unsigned char b)
{
	*color = (*color << 16 & ((*color << 16) / 2 + r / 2));
	*color = (*color << 8 & ((*color << 8) / 2 + g / 2));
	*color = (*color << 0 & ((*color << 0) / 2 + b / 2));
}
