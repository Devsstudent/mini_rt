/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_equation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:05:56 by odessein          #+#    #+#             */
/*   Updated: 2022/12/12 16:42:28 by odessein         ###   ########.fr       */
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
	printf("%f %f %f\n", original_pos.x, original_pos.y, original_pos.z);
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

t_xyz	get_vec_horizontal(t_xyz v_director, t_xyz v_ortho)
{
	t_xyz	res;

	res.x = v_director.y * v_ortho.z - v_director.z * v_ortho.y;
	res.y = v_director.z * v_ortho.x - v_director.x * v_ortho.z;
	res.z = v_director.x * v_ortho.y - v_director.y * v_ortho.x;
	return (res);
}

int	render_window(void	*objss)
{
	t_xyz	vector_width;
	t_xyz	vector_height;
	t_objects	*objs;

	objs = ((t_objects *) objss);
	printf("%f %f %f\n", objs->cam->vec_direction.x,  objs->cam->vec_direction.y,  objs->cam->vec_direction.z );
	vector_height = get_vec_vertical(objs->cam->vec_direction);
	if (!vector_height.x && !vector_height.y && !vector_height.z)
		return (2);
	vector_width = get_vec_horizontal(objs->cam->vec_direction, vector_height);
	vector_height = get_screen_unit_vert_vect(vector_width, vector_height, (WIN_W / WIN_H));
	vector_width = get_screen_unit_hor_vect(objs->cam->vec_direction, vector_width, objs->cam->fov, WIN_W);
	loop(objs->mlx, vector_height, vector_width, objs->cam->position, objs->cam->vec_direction);
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
