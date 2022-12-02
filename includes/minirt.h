/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:39:07 by odessein          #+#    #+#             */
/*   Updated: 2022/12/02 18:20:35 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <stdbool.h>
# include "error.h"
# include "parsing.h"
# include "libft.h"

typedef struct s_xyz {
	float	x;
	float	y;
	float	z;
}		t_xyz;

typedef struct s_rgb {
	uint_8	R; //0-255
	uint_8	G; //0-255
	uint_8	B; //0-255
}					t_rgb;

typedef struct s_orientation{
	float	x; //-1 1 0 20
	float	y; //-1 1
	float	z; //-1 1
}			t_orientation;

typedef struct s_ambient_light
{
	uint_8	ratio; //0 1 2 3 4 5 6 7 8 9 10
	t_rgb			color;
}					t_ambient_light;

typedef struct s_camera
{
	t_xyz			position;
	t_orientation	vec_direction;
	uint_8	fov; //0-180
}					t_camera;

typedef struct s_light {
	t_xyz			position;
	uint_8	ratio; //0 1 2 3 4 5 6 7 8 9 10
	t_rgb			color;
}					t_light;

typedef struct s_sphere {
	t_xyz			position;
	unsigned float	diameter;
	t_rgb			color;
}					t_sphere;

typedef struct	s_plane {
	t_xyz			position;
	t_orientation	vec_direction;
	t_rgb			color;
}					t_plane;

typedef struct	s_cylinder {
	t_xyz			position;
	t_orientation	vec_direction;
	unsigned float	diameter;
	unsigned float	height;
	t_rgb			color;
}					t_cylinder;

typedef struct	s_objects {
	t_cylinder		*cy;
	t_plane			*pl;
	t_sphere		*sp;
	t_light			*li;
	t_camera		*cam;
	t_ambient_light	*amb;
}	t_objects;

#endif
