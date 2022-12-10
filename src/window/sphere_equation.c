/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_equation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:05:56 by odessein          #+#    #+#             */
/*   Updated: 2022/12/09 16:24:15 by odessein         ###   ########.fr       */
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



t_xyz	get_vec_vertical(t_xyz original_pos)
{
	t_xyz	res;

	res.x = 0;
	res.y = 0;
	res.z = 0;
	if (original_pos.x == 0 && original_pos.y == 0 && original_pos.z == 0)
	{
		write(2, "Not possible to get the orthogonal vector\n", ft_strlen("Not possible to get the orthogonal vector\n"));
		return (res);
	}
	if (original_pos.z != 0)
	{
		res.z = (-((2) * original_pos.x) / original_pos.z - (( 4 * original_pos.y) / original_pos.z));
		res.x = 2;
		res.y = 4;
	}
	else if (original_pos.y != 0)
	{
		res.y = (-((2) * original_pos.x) / original_pos.y - (( 4 * original_pos.z) / original_pos.y));
		res.x = 2;
		res.z = 4;
	}
	else if (original_pos.x != 0)
	{
		res.x = (-((2) * original_pos.y) / original_pos.x - (( 4 * original_pos.z) / original_pos.x));
		res.y = 2;
		res.z = 4;
	}
	return (res);
}

t_xyz	get_oppo(t_xyz right_pos)
{
	t_xyz	res;

	res.x = -right_pos.x;
	res.y = -right_pos.y;
	res.z = -right_pos.z;
	return (res);
}

t_xyz	get_vec_horizontal(t_xyz v_director, t_xyz v_ortho)
{
	t_xyz	res;

	res.x = v_director.y * v_ortho.z - v_director.z * v_ortho.y;
	res.y = v_director.z * v_ortho.x - v_director.x * v_ortho.z;
	res.z = v_director.x * v_ortho.y - v_director.y * v_ortho.x;
	return (res);
}

float	norm_of_vector(t_xyz vector)
{
	float	res;

	res = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
	return (res);
}

void	normalizing(t_xyz *vector, float vector_norm, float window_scale)
{
	if (window_scale == 0 || vector_norm == 0)
	{
		ft_putstr_fd("Error dividing by zero in normalizing\n", 2);
		return ;
	}
	vector->x = (vector->x / (window_scale * vector_norm));
	vector->y = (vector->y / (window_scale * vector_norm));
	vector->z = (vector->z / (window_scale * vector_norm));
}

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
