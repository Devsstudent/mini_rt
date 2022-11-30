/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:39:07 by odessein          #+#    #+#             */
/*   Updated: 2022/11/30 14:52:18 by odessein         ###   ########.fr       */
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
	int	x;
	int	y;
	int	z;
}		t_xyz;

typedef struct s_rgb {
	unsigned char	R; //0-255
	unsigned char	G; //0-255
	unsigned char	B; //0-255
}					t_rgb;

typedef struct s_orientation{
	float	x; //-1 1 0 20
	float	y; //-1 1
	float	z; //-1 1
}			t_orientation;

typedef struct s_ambient_light
{
	unsigned char	ratio; //0 1 2 3 4 5 6 7 8 9 10
	t_rgb			color;
}					t_ambient_light;

typedef struct s_camera
{
	t_xyz			position;
	t_orientation	vec_direction;
	unsigned char	fov; //0-180
}					t_camera;

typedef struct s_light {
	t_xyz			position;
	unsigned char	ratio; //0 1 2 3 4 5 6 7 8 9 10
	t_rgb			color;
}					t_light;

typedef struct s_sphere {
	t_xyz			position;
	unsigned int	diameter;
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
	unsigned int	diameter;
	unsigned int	height;
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
