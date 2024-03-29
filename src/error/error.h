/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:45:55 by odessein          #+#    #+#             */
/*   Updated: 2023/02/01 16:19:32 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ERROR_H
# define ERROR_H

# include "minirt.h"

typedef struct s_plane			t_plane;
typedef struct s_sphere			t_sphere;
typedef struct s_cylinder		t_cylinder;
typedef struct s_cone			t_cone;
typedef struct s_xyz			t_xyz;
typedef struct s_rgb			t_rgb;
typedef struct s_orientation	t_orientation;
typedef struct s_objects		t_objects;
typedef struct s_sol_li			t_sol_li;
typedef struct s_disp_point		t_disp_point;

//error.c
void			error_msg(char *str);
void			free_exit(void *objs);
void			free_objs(t_objects *obj);
void			free_list_exit(t_objects *objss, t_sol_li *list);
t_disp_point	error_intersec(void);

//free_objs.c
void			free_cy(t_objects *objs, t_cylinder *cy);
void			free_pl(t_objects *objs, t_plane *pl);
void			free_sp(t_objects *objs, t_sphere *sp);
void			free_co(t_objects *objs, t_cone *co);

//free_structs_utils.c
void			free_structs(t_objects *objects);
void			free_double_arr(char **double_arr);
void			free_triple_arr(char ***triple_arr);
#endif
