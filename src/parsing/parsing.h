/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:55:57 by odessein          #+#    #+#             */
/*   Updated: 2022/11/29 16:13:09 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSING_H
# define PARSING_H
# include <stdbool.h>
typedef struct s_must_have {
	bool	ambient;
	bool	camera;
	bool	object;
}			t_must_have;

//utils.c
bool	free_split_return_false(char **line_split);
bool	ft_is_space(char c);

//split_on_function.c
char	**split_func_condition(char const *s, bool (*f)(char));

#endif