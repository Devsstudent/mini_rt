#include "head.h"
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	t_solution_list	*head;
	t_solution		ahha;
	t_rgb			color;
	t_type			type;

	type = SP;
	memset(&ahha, 0, sizeof(ahha));
	memset(&color, 0, sizeof(color));
	head = malloc(sizeof(1));
	free(head);
	return (0);
	int	i;
	i = 0;
	while (i < 100)
	{
		int	j;
		j =0;
		while (j < 300)
		{
			list_add(&head, new_elem(ahha, color, type, j));
			j++;
		}
		free_list(&head);
		i++;
	}
}
