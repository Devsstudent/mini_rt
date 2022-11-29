/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_on_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:48:01 by odessein          #+#    #+#             */
/*   Updated: 2022/11/29 16:13:42 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "minirt.h"
#include "parsing.h"
#include <stdlib.h>

static char	*ft_strndup(char *s, size_t n)
{
	char	*res;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	if (n > len)
		n = len;
	res = (char *) malloc(sizeof(char) * (n + 1));
	if (!res)
		return (NULL);
	while (s[i] != '\0' && i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static char	**ft_less_line(char *s, bool (*f)(char), int *i, char **res)
{
	size_t	j;
	int		k;
	char	*temp;

	k = 0;
	while (s[++(*i)] != '\0')
	{
		j = 0;
		if (s[(*i)] && !(*f)(s[(*i)]))
		{
			temp = &s[*i];
			while (s[(*i)] != '\0' && !(*f)(s[(*i)]))
			{
				(*i)++;
				j++;
			}
			res[k] = ft_strndup(temp, j);
			k++;
			(*i)--;
		}
	}
	res[k] = NULL;
	return (res);
}

static char	**ft_count_word(char *s, bool (*f)(char))
{
	char	**res;
	int		size;

	size = 0;
	while (*s && (*f)(*s))
		s++;
	while (*s)
	{
		if (!(*f)(*s))
		{
			while (*s && !(*f)(*s))
				s++;
			size++;
		}
		while (*s && (*f)(*s))
			s++;
	}
	res = (char **) malloc(sizeof(*res) * (size + 1));
	if (!res)
		return (NULL);
	return (res);
}

char	**split_func_condition(char const *s, bool (*f)(char))
{
	char	**res;
	int		i;

	res = NULL;
	i = -1;
	if (!s)
		return (res);
	res = ft_count_word((char *) s, f);
	res = ft_less_line((char *) s, f, &i, res);
	return (res);
}
