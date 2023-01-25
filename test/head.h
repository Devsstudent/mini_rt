/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:05:04 by odessein          #+#    #+#             */
/*   Updated: 2023/01/25 11:31:59 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef HEAD_H
# define HEAD_H

# include <stdint.h>
# include <stdbool.h>

typedef float t_vect __attribute__ ((vector_size(16)));
typedef struct s_xyz {
	float	x;
	float	y;
	float	z;
}		t_xyz;

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

typedef struct s_rgb {
	uint8_t	B; //0-255
	uint8_t	G; //0-255
	uint8_t	R; //0-255
	uint8_t	T; //0-255
}					t_rgb;

typedef struct s_solution_list {
	t_rgb					color;
	t_solution				solution;
	t_type					type;
	int						obj_id;
	struct s_solution_list	*next;
}							t_solution_list;


t_solution_list	*new_elem(t_solution solution, t_rgb color, t_type type, int i);
bool	list_add(t_solution_list **head, t_solution_list *new);
void	free_list(t_solution_list **head);
#endif
