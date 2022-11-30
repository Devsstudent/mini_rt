/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_store_content_rt.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:17:04 by odessein          #+#    #+#             */
/*   Updated: 2022/11/30 15:28:25 by odessein         ###   ########.fr       */
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
		if (line && line[0] != '\n')
		{
			i++;
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!check_line(line, arr, all_elem))
		{
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
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

bool	open_and_store(char *name, char **lines)
{
	int					fd;
	int					line_nbr;
	t_must_have			all_elem;
	t_function_parsing	*arr;

	//FILL array of function_parsing
	line_nbr = 0;
	arr = NULL;
	init_all_elem(&all_elem);
	setup_array_function(arr);
	if (!get_line_nb_checking_line(name, arr, &line_nbr, &all_elem))
		return (free_array_function(arr));
	lines = malloc(sizeof(*lines) * (line_nbr + 1));
	if (!lines)
	{
		perror("Error\n");
		return (false);
	}
	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		free(lines);
		perror("Error\n");
		return (false);
	}
	if (!fill_lines(lines, fd, line_nbr))
	{
		//GNL ERROR ?
		close(fd);
		free_double_arr(lines);
		perror("Error\n");
		return (false);
	}
	close(fd);
	return (true);
}
