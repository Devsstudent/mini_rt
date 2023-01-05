/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_equation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:05:56 by odessein          #+#    #+#             */
/*   Updated: 2023/01/05 17:54:20 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

//Need to find those 2 point where the circle hit y = 0;
//En fonction de la position de la camera on obtient 2 point de la droite;

//Point de depart (camera position)
//Point d'arriver (j


//Calculate viewplane (what we will display)
	//Depending on FOV, to know where to send the first ray
		//first ray = left corner pixel in viewplan ! etc 
	//each ray = position camera + (vecteur de direction * t)

//Definition of the viewplan / FOV : viewpPlanWidth viewPlanHeight viewPlanDist 
//Pixel corner gauche = CamPos + ((VecDir*vierplaneDist) + (vecUp * viewplaneHeight/2) - (Vecright*viewplaneWidth/2))

//A partir de ce pixel : cornerleft + rightvec * Xindent * x - upvec * yindent * y
//On a tous les pixel
//Ainsi que leurs vecteur unitaire

//xindent = viewplaneWidth / (float)xRes; (xRes = 1920)  (1920 * 1080 resoltion)
//yindent = vireplandHeight / (float)yRes; (yRes = 1080) (1920 * 1080 resoltion)
//Ces valeurs dépdendent du fov (field of vision), de la caméra, cependant nous allons assummer pour le moment que la largeur est de 0.35, la hauteur de 0.5 et la distance de 1.0. ?? How to define thos variable from the fov ..


t_vect	get_vec_vertical(t_vect original_pos)
{
	t_vect	res;

	res[0] = 0;
	res[1] = 0;
	res[2] = 0;
	if (original_pos[0] == 0 && original_pos[1] == 0 && original_pos[2] == 0)
	{
		write(2, "Not possible to get the orthogonal vector\n", ft_strlen("Not possible to get the orthogonal vector\n"));
		return (res);
	}
	if (original_pos[0] == 0 && original_pos[1] == 0 && original_pos[2] > 0)
	{
		res[1] = 1;
		return (res);
	}
	if (original_pos[2] != 0)
	{
		res[2] = (-((2) * original_pos[0]) / original_pos[2] - (( 4 * original_pos[1]) / original_pos[2]));
		res[0] = 2;
		res[1] = 4;
	}
	else if (original_pos[1] != 0)
	{
		res[1] = (-((2) * original_pos[0]) / original_pos[1] - (( 4 * original_pos[2]) / original_pos[1]));
		res[0] = 2;
		res[2] = 4;
	}
	else if (original_pos[0] != 0)
	{
		res[0] = (-((2) * original_pos[1]) / original_pos[0] - (( 4 * original_pos[2]) / original_pos[1]));
		res[1] = 2;
		res[2] = 4;
	}
	return (res);
}

t_vect	get_vec_horizontal(t_vect v_director, t_vect v_ortho)
{
	t_vect	res;

	if (v_director[0] == 0 && v_director[1] == 0 && v_director[2] > 0
			&& v_ortho[0] == 0 && v_ortho[1] > 0 && v_ortho[2] == 0)
	{
		res[0] = 1;
		res[1] = 0;
		res[2] = 0;
	}
	res[0] = v_director[1] * v_ortho[2] - v_director[2] * v_ortho[1];
	res[1] = v_director[2] * v_ortho[0] - v_director[0] * v_ortho[2];
	res[2] = v_director[0] * v_ortho[1] - v_director[1] * v_ortho[0];
	return (res);
}

//HFOV_rad = FOV * PI / 180;

//VFOV_rad = 2 * arctan(tan(HFOV_rad/2) * W * H)

//VFOV_degree = VFOV_rad * 180 / PI

//Resolve quadratic equation
	//start from 0,0
	//to 0 - FOV/2
	//to 0 + FOV/2

	//checker les solutions
	//pixel_put
	//avancee dans la loop
