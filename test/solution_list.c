/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:04:47 by odessein          #+#    #+#             */
/*   Updated: 2023/01/10 18:21:28 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "head.h"
#include <stdlib.h>

bool	list_add(t_solution_list **head, t_solution_list *new)
{
	t_solution_list	*buff;

	if (!head)
		return (false);
	if (!(*head))
	{
		*head = new;
		return (true);
	}
	buff = *head;
	while (buff->next != NULL)
		buff = buff->next;
	buff->next = new;
	return (true);
}

t_solution_list	*new_elem(t_solution solution, t_rgb color, t_type type, int i)
{
	t_solution_list	*res;

	res = malloc(sizeof(t_solution_list));
	if (!res)
		return (NULL);
	res->solution = solution;
	res->color = color;
	res->type = type;
	res->obj_id = i;
	res->next = NULL;
	return (res);
}

t_solution_list	*get_last_elem(t_solution_list **head)
{
	t_solution_list	*last;

	last = *head;
	while (last->next != NULL)
	{
		last = last->next;
	}
	return (last);
}

void	free_list(t_solution_list **head)
{
	t_solution_list	*buff;

	while (*head != NULL)
	{
		buff = (*head)->next;
		free(*head);
		*head = buff;
	}
}
