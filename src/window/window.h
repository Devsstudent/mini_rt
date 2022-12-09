/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:53:13 by odessein          #+#    #+#             */
/*   Updated: 2022/12/09 16:23:18 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef WINDOW_H
# define WINDOW_H
# define ESC 65307
# define WIN_W 780
# define WIN_H 540
# include "minirt.h"

typedef struct s_xyz			t_xyz;
typedef struct s_rgb			t_rgb;
typedef struct s_orientation	t_orientation;
typedef struct s_objects		t_objects;
typedef void * t_mlx;

typedef struct s_mlx_info {
	t_mlx	*mlx;
	t_mlx	*win;
}			t_mlx_info;

typedef struct s_equation {
	float	x_pow_two;
	float	x_pow_one;
	float	c;
}				t_equation;

bool	window(t_objects *objs, t_mlx_info *mlx);


t_xyz	get_vec_vertical(t_xyz original_pos);
t_xyz	get_oppo(t_xyz right_pos);
t_xyz	get_vec_horizontal(t_xyz v_director, t_xyz v_ortho);
float	norm_of_vector(t_xyz vector);
void	normalizing(t_xyz *vector, float vector_norm, float window_scale);
void	render_window(t_objects objs);
t_equation	get_circle_equation(float ax, float bx, float ay, float by, float r);

#endif
