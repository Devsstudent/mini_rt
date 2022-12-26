/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:03:54 by odessein          #+#    #+#             */
/*   Updated: 2022/12/26 18:58:09 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	create_color(t_rgb rgb, float RGB[3])
{
	int	color;

	color = 0;
	color |= (int)trunc((float)rgb.R * RGB[0]);
	color = color << 8;
	color |= (int)trunc((float)rgb.G * RGB[1]);
	color = color << 8;
	color |= (int)trunc((float)rgb.B * RGB[2]);
	return (color);
}

void	add_color(int *color, t_rgb rgb)
{
	*color = (*color << 16 & ((*color << 16) / 2 + rgb.R / 2));
	*color = (*color << 8 & ((*color << 8) / 2 + rgb.G / 2));
	*color = (*color << 0 & ((*color << 0) / 2 + rgb.B / 2));
}

void	ambient_light_quo(t_objects *objs, float RGB[3])
{
	RGB[0] = (float)objs->amb->color.R * objs->amb->ratio / 255.0;
	RGB[1] = (float)objs->amb->color.G * objs->amb->ratio / 255.0;
	RGB[2] = (float)objs->amb->color.B * objs->amb->ratio / 255.0;
	//rgb->R = trunc((float)rgb->R * R);
	//rgb->G = trunc((float)rgb->G * G);
	//rgb->B = trunc((float)rgb->B * B);
}

/*
void	add_light(t_disp_point disp_p, t_objects *objs)
{
	// si ca intersecte pas, on ajoute la lumiere a la bonne intensite en fonction de la distance, sinon on ajoute pas la lumiere
	//pour l'instant addition meme si pas ca dans la realite
	t_line_eq	rayline;
	//faire en sorte que ce soit pas forcement camera pour la rayline in get_plane and get_sphere
}
*/

bool	get_pixel_color(int *color, t_disp_point disp_p, t_objects *objs)
{
	t_rgb	color_rgb;
	float	RGB[3];

	RGB[0] = 0;
	RGB[1] = 0;
	RGB[2] = 0;
	color_rgb.R = disp_p.color.R;
	color_rgb.G = disp_p.color.G;
	color_rgb.B = disp_p.color.B;
	//*color = create_color(disp_p.color);
	ambient_light_quo(objs, RGB);
//	add_light(disp_p, objs, RGB);
	*color = create_color(color_rgb, RGB);
	return (true);
}
