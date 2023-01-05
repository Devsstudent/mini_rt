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

int	render_window(void	*objss)
{
	t_vect	vector_width;
	t_vect	vector_height;
	t_viewplan	view_plan;
	t_objects	*objs;

	objs = (t_objects *) objss;
	//printf("%f %f %f\n", objs->cam->vec_direction[0],  objs->cam->vec_direction[1],  objs->cam->vec_direction[2] );
	vector_height = get_vec_vertical(objs->cam->vec_direction);
	if (!vector_height[0] && !vector_height[1] && !vector_height[2])
		return (2);
	vector_width = get_vec_horizontal(objs->cam->vec_direction, vector_height);
	view_plan.hori = get_screen_unit_hor_vect(objs->cam->vec_direction, vector_width, objs->cam->fov);
	view_plan.verti = get_screen_unit_vert_vect(view_plan.hori, vector_height);
	view_plan.up_left = get_up_left(view_plan.hori, view_plan.verti, objs->cam->vec_direction);
	loop_rendering(objs, view_plan);
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
