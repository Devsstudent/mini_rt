/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:53:13 by odessein          #+#    #+#             */
/*   Updated: 2022/12/16 19:08:41 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef WINDOW_H
# define WINDOW_H
# define ESC 65307
# define PI 3.1415926535
# define WIN_W 780
# define WIN_H 540
# include "minirt.h"

typedef float t_vect __attribute__ ((vector_size(16)));
typedef struct s_xyz			t_xyz;
typedef struct s_rgb			t_rgb;
typedef struct s_orientation	t_orientation;
typedef struct s_objects		t_objectss;
typedef void * t_mlx;

typedef struct s_mlx_info {
	t_mlx	*mlx;
	t_mlx	*win;
	t_mlx	*img;
	int		bpp;
	int		line_size;
	int		endian;
	char	*data;
}			t_mlx_info;

typedef struct s_equation {
	float	x_pow_two;
	float	x_pow_one;
	float	c;	
}				t_equation;

typedef struct s_viewplan{
	t_vect	hori;
	t_vect	verti;
	t_vect	up_left;
}			t_viewplan;

typedef struct s_eq{
	float	c;
	float	t;
}		t_eq;

typedef struct s_line_eq {
	t_eq	x;
	t_eq	y;
	t_eq	z;
}		t_line_eq;

typedef struct s_solution{
	t_xyz	*one;
	t_xyz	*two;
	bool	sol_one;
	bool	sol_two;
}		t_solution;

typedef enum e_elem_type{
	CY,
	PL,
	SP,
}	t_elem_type;

typedef struct s_solution_list {
	t_elem_type				type;
	t_solution				solution;
	struct s_solution_list	*next;
}							t_solution_list;

	//raytracing.c
t_vect	get_up_left(t_vect hori, t_vect verti, t_vect orient);
	bool	get_sphere(t_objects *obj, t_viewplan *viewplan, t_solution_list **list, t_vect rayvec);
	bool	get_plane(t_objects *obj, t_viewplan *viewplan, t_solution_list **list, t_vect rayvec);
	bool	loop_rendering(t_objects *objs, t_viewplan view_plan);
bool	loop_line(t_objects *objs, t_viewplan *view_plan, int i);
	t_line_eq	get_rayline_eq(t_vect vec_line, t_xyz start_point);
	t_vect	get_vector(t_vect hori, t_vect verti, t_vect orient);
	t_equation	get_quadra_sphere_equation(t_line_eq rayline, t_objectss *objs);
	t_equation	get_quadra_plan_equation(t_line_eq rayline, t_objectss *objs);
bool	check_intersection(t_viewplan view_plan, t_objects *objs, t_solution_list **list);

	//equation.c
	bool	one_solu(t_solution *solu, t_equation eq, t_line_eq equation);
	bool	two_solu(t_solution *solu, t_equation eq, t_line_eq equation);
	t_solution	solution(t_equation eq, t_line_eq equation, bool *error);

	//sphere_equations.c
	t_vect	get_vec_vertical(t_vect original_pos);
	t_vect	get_vec_horizontal(t_vect v_director, t_vect v_ortho);
	int		render_window(void	*objss);

	//loop_mlx.c
	void	img_pixel_put(t_mlx_info *mlx, int j, int i, int color);
	int	close_window(t_mlx_info *mlx);
	int	hook_press(int keycode, t_mlx_info *mlx);
	int	hook_release(int keycode, t_mlx_info *mlx);
	void	img_pixel_put(t_mlx_info *mlx, int j, int i, int color);
bool	window(t_objectss *objs);

//vector_opperation.c
t_vect	get_orthogonal_vect(t_vect vector);
t_vect	get_opposite_vector(t_vect vector);
t_vect	vector_product(t_vect vector_1, t_vect vector_2);
float	norm_of_vector(t_vect vector);
t_vect	normalize_vector(t_vect vector);
t_vect	get_screen_unit_vert_vect(t_vect unit_w, t_vect vect_h);
t_vect	get_screen_unit_hor_vect(t_vect vect_d, t_vect vect_w, int fov);

//solution_list
bool	list_add(t_solution_list **head, t_solution_list *new);
void	free_list(t_solution_list **head);
t_solution_list	*new_elem(t_elem_type type, t_solution solution);
#endif
