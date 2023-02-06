/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_w_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:52:16 by alevra            #+#    #+#             */
/*   Updated: 2023/02/06 22:43:11 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	how_many_args(char **str);
static char	*dup_w_quotes(char *str);

char	**get_args_w_flags(char **splits)
{
	char	**args;
	int		i;
	int		j;
	char	space;
	char	*tmp;
	char	quote;

	space = ' ';
	i = 0;
	j = 0;
	args = malloc(sizeof(char *) * how_many_args(splits));
	while (splits[i])
	{
		args[j] = ft_strdup(splits[i]);
		i ++;
		while (splits[i] && splits[i][0] == '-')
		{
			tmp = ft_strjoin(args[j], (const char *)&space);
			free(args[j]);
			args[j] = tmp;
			tmp = ft_strjoin(args[j], splits[i]);
			free(args[j]);
			args[j] = tmp;
			i++;
		}
		args[j] = dup_w_quotes(args[j]);
		j++;
	}
	args[j] = (char *)0;
	return (args);
}

static char	*dup_w_quotes(char *str)
{
	char	*res;
	char	*tmp;
	const char	*quote = "\"";

	tmp = ft_strdup(str);
	free(str);
	res = ft_strjoin(quote, tmp);
	free(tmp);
	tmp = ft_strjoin(res, quote);
	res = tmp;
	return (res);
}

static int	how_many_args(char **str)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i][0] != '-')
			res++;
		i++;
	}
	return (res);
}
