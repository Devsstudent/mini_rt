/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:04:47 by odessein          #+#    #+#             */
/*   Updated: 2022/12/16 19:15:37 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

bool	list_add(t_solution_list *head, t_solution_list new)
{
	t_solution_list	buff;

	if (!head)
		return (false);
	if (!(*head))
	{
		head = new;
		return (true);
	}
	buff = *head;
	while (buff->next != NULL)
		buff = buff->next;
	buff->next = &new;
	return (true);
}

t_solution_list	new_elem(t_elem_type type, t_solution solution)
{
	t_solution_list	res;

	res.type = type;
	res.solution = solution;
	return (res);
}
