/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:04:47 by odessein          #+#    #+#             */
/*   Updated: 2023/02/01 20:33:42 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

void	init_sol_li(t_sol_li *sol_li)
{
	sol_li->size = 0;
	sol_li->head = NULL;
	sol_li->last = NULL;
}

bool	list_add(t_sol_li *sol_li, t_solution_elem *new)
{
	t_solution_elem	*buff;

	if (!sol_li || !new)
		return (false);
	if (!sol_li->head)
	{
		sol_li->head = new;
		return (true);
	}
	buff = sol_li->head;
	while (buff->next != NULL)
		buff = buff->next;
	buff->next = new;
	sol_li->size += 1;
	sol_li->last = new;
	return (true);
}

t_solution_elem	*new_elem(t_solution solution, t_new_elem_info info)
{
	t_solution_elem	*res;

	res = (t_solution_elem *) malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->solution = solution;
	res->color = info.color;
	res->type = info.type;
	res->obj_id = info.i;
	res->tex = info.tex;
	res->next = NULL;
	return (res);
}

void	free_list(t_sol_li *sol_li)
{
	t_solution_elem	*buff;

	while (sol_li->head != NULL)
	{
		buff = sol_li->head->next;
		free(sol_li->head);
		sol_li->head = buff;
	}
}

void	fill_info(t_new_elem_info *info, t_rgb color, int i, t_obj_texture tex)
{
	info->color = color;
	info->tex = tex;
	info->i = i;
}
