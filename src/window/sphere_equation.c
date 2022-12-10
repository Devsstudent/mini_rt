/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_equation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:05:56 by odessein          #+#    #+#             */
/*   Updated: 2022/12/10 18:37:56 by mbelrhaz         ###   ########.fr       */
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


void	render_window(t_objects objs)
{
	t_xyz	vector_width;
	t_xyz	vector_height;
	float	width_norm;

	vector_height = get_vec_vertical(objs.cam->vec_direction);
	if (!vector_height.x && !vector_height.y && !vector_height.z)
		return ;
	vector_width = get_vec_horizontal(objs.cam->vec_direction, vector_height);
	width_norm = tan(objs.cam->fov) / norm_of_vector(objs.cam->vec_direction);
	width_norm *= 2;
	normalizing(&vector_height, norm_of_vector(vector_height), width_norm);
	normalizing(&vector_width, norm_of_vector(vector_width), width_norm * (WIN_W / WIN_H));
	//To get up_left
	//We have to define 1 vector (for left_right)
	//We have to define 1 vector (for up_down)
}

t_equation	get_circle_equation(float ax, float bx, float ay, float by, float r)
{
	t_equation	res;

	res.x_pow_two = (pow(bx, 2) + pow(by, 2));
	res.x_pow_one = 2 * (ax * bx) + 2 * (ay * by);
	res.c = pow(ax, 2) + pow(ay, 2) - pow(2, r);
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
