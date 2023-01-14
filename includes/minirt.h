/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:39:07 by odessein          #+#    #+#             */
/*   Updated: 2023/01/14 22:07:43 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <stdint.h>
# include <stdbool.h>
# include "mlx.h"
# include "mlx_int.h"
# include "error.h"
# include "parsing.h"
# include "libft.h"
# include "window.h"
# include "edit.h"

# define PI 3.1415926535

typedef float t_vect __attribute__ ((vector_size(16)));
typedef struct s_mlx_info t_mlx_info;
typedef struct s_disc_info t_disc_info;

typedef struct s_xyz {
	float	x;
	float	y;
	float	z;
}		t_xyz;

typedef struct s_rgb {
	uint8_t	B; //0-255
	uint8_t	G; //0-255
	uint8_t	R; //0-255
	uint8_t	T; //0-255
}					t_rgb;

typedef union u_color {
	t_rgb	rgb;
	int	color;
}		t_color;

typedef struct s_orientation{
	float	x; //-1 1 0 20
	float	y; //-1 1
	float	z; //-1 1
}			t_orientation;

typedef enum e_edit_type {
	UNDEF,
	RESIZE,
	RESIZE_WIDTH,
	ROTATE,
	TRANSLATE
}	t_edit_type;

typedef struct s_ambient_light
{
	float			ratio; //0 1 2 3 4 5 6 7 8 9 10
	t_rgb			color;
}					t_ambient_light;

typedef struct s_camera
{
	t_xyz		position;
	t_vect		vec_direction;
	uint8_t		fov; //0-180
}				t_camera;

typedef struct s_light {
	t_xyz			position;
	float			ratio; //0 1 2 3 4 5 6 7 8 9 10
	t_rgb			color;
}					t_light;

typedef struct s_sphere {
	t_xyz		position;
	float		diameter;
	t_rgb		color;
}				t_sphere;

typedef struct	s_plane {
	t_xyz	position;
	t_vect	vec_direction;
	t_rgb	color;
}			t_plane;

typedef struct	s_cylinder {
	t_xyz			position;
	float			xm_2[3];
	t_vect			vec_direction;
	float			abc_2[3];
	float			diameter;
	float			radius;
	float			radius_2;
	float			height;
	t_rgb			color;
}					t_cylinder;

typedef struct	s_disc_info {
	t_xyz	p_disc;
	float	radius;
}				t_disc_info;

typedef struct s_solution {
	t_xyz	one;
	t_xyz	two;
	bool	sol_one;
	bool	sol_two;
}		t_solution;

typedef enum e_type{
	SP,
	CY,
	PL,
	C,
	LI
}	t_type;

typedef enum e_axis{
	NO_ONE,
	X,
	Y,
	Z
}	t_axis;

typedef struct s_solution_elem {
	t_rgb					color;
	t_solution				solution;
	t_type					type;
	int						obj_id;
	struct s_solution_elem	*next;
}							t_solution_elem;

typedef struct s_sol_li {
	t_solution_elem	*head;
	int				size;
	t_solution_elem	*last;
}					t_sol_li;

typedef struct s_disp_point{
	t_xyz		intersec_point;
	t_rgb		color;
	t_type		type;
	int			obj_id;
	bool		err;
}				t_disp_point;

typedef struct s_color_pam{
	float			distance;
	float			diffuse;
	float			specular;
	t_disp_point	disp_p;
	t_vect			rayvec;
}			t_color_pam;

typedef struct s_edit {
	t_edit_type	action;
	t_xyz		coord;
	long		width;
	long		height;
	long		diameter;
	int			angle;
	t_axis		axis;
}			t_edit;

typedef struct	s_cy_eq {
	float		r;
	float		r_2;
	float		a;
	float		b;
	float		c;
	float		a_2;
	float		b_2;
	float		c_2;
	float		xm;
	float		ym;
	float		zm;
	float		xm_2;
	float		ym_2;
	float		zm_2;
	float		i;
	float		j;
	float		k;
	float		i_2;
	float		j_2;
	float		k_2;
	float		xp;
	float		yp;
	float		zp;
	float		xp_2;
	float		yp_2;
	float		zp_2;
}			t_cy_eq;

typedef struct	s_objects {
	t_vect			vect_height;
	t_vect			vect_width;
	t_sphere		*sp;
	int			nb_sp;
	t_cylinder		*cy;
	int			nb_cy;
	t_light			*li;
	int			nb_li;
	t_plane			*pl;
	int			nb_pl;
	t_camera		*cam;
	t_ambient_light	*amb;
	t_mlx_info		*mlx;
	bool		need_display;
	int			nb_elem;
	bool			edited;
}	t_objects;

#endif
