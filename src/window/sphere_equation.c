/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_equation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:05:56 by odessein          #+#    #+#             */
/*   Updated: 2022/12/14 17:06:39 by mbelrhaz         ###   ########.fr       */
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
	//printf("%f %f %f\n", original_pos.x, original_pos.y, original_pos.z);
	if (original_pos[0] == 0 && original_pos[1] == 0 && original_pos[2] == 0)
	{
		write(2, "Not possible to get the orthogonal vector\n", ft_strlen("Not possible to get the orthogonal vector\n"));
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

	res[0] = v_director[1] * v_ortho[2] - v_director[2] * v_ortho[1];
	res[1] = v_director[2] * v_ortho[0] - v_director[0] * v_ortho[2];
	res[2] = v_director[0] * v_ortho[1] - v_director[1] * v_ortho[0];
	return (res);
}

int	render_window(void	*objss)
{
	t_vect	vector_width;
	t_vect	vector_height;
	t_vect	pixel_width;
	t_vect	pixel_height;
	t_objects	*objs;

	objs = (t_objects *) objss;
	//printf("%f %f %f\n", objs->cam->vec_direction.x,  objs->cam->vec_direction.y,  objs->cam->vec_direction.z );
	vector_height = get_vec_vertical(objs->cam->vec_direction);
	if (!vector_height[0] && !vector_height[1] && !vector_height[2])
		return (2);
	vector_width = get_vec_horizontal(objs->cam->vec_direction, vector_height);
	pixel_width = get_screen_unit_hor_vect(objs->cam->vec_direction, vector_width, objs->cam->fov);
	pixel_height = get_screen_unit_vert_vect(pixel_width, vector_height);
	loop(objs->mlx, pixel_height, pixel_width, objs->cam->position, objs->cam->vec_direction, objs);
	//To get up_left
	//We have to define 1 vector (for left_right)
	//We have to define 1 vector (for up_down)
	return (1);
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
