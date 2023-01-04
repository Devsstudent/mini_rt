/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_store_content_rt.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:17:04 by odessein          #+#    #+#             */
/*   Updated: 2023/01/04 14:50:03 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static int	line_nb(int fd, t_must_have *all_elem, t_function_parsing *arr)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line && line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!check_line(line, arr, all_elem))
			return (free(line), 0);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (!check_all_elem(*all_elem))
		return (0);
	return (i);
}

static bool	fill_lines(char **lines, int fd, int line_nb)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line && line[0] != '\n')
			lines[i++] = line;
		else
			free(line);
		line = get_next_line(fd);
	}
	if (i != line_nb)
		return (false);
	return (true);
}

static bool	get_line_nb_checking_line(char *name, t_function_parsing *arr,
				int *line_nbr, t_must_have *all_elem)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\n");
		return (false);
	}
	*line_nbr = line_nb(fd, all_elem, arr);
	close(fd);
	if (*line_nbr == 0)
	{
		ft_putstr_fd("Error\n Invalid Map", 2);
		return (false);
	}
	free_array_function(arr);
	return (true);
}

char	**open_and_store(char *name)
{
	int					fd;
	int					line_nbr;
	char				**lines;
	t_must_have			all_elem;
	t_function_parsing	*arr;

	line_nbr = 0;
	arr = NULL;
	init_all_elem(&all_elem);
	setup_array_function(&arr);
	if (!get_line_nb_checking_line(name, arr, &line_nbr, &all_elem))
		return (free_array_function(arr), NULL);
	lines = malloc(sizeof(*lines) * (line_nbr + 1));
	if (!lines)
		return (perror("Error\n"), NULL);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (free(lines), perror("Error\n"), NULL);
	if (!fill_lines(lines, fd, line_nbr))
		return (close(fd), free_double_arr(lines), perror("Error\n"), NULL);
	close(fd);
	lines[line_nbr] = NULL;
	return (lines);
}
