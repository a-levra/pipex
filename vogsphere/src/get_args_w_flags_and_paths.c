/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_w_flags_and_paths.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:52:16 by alevra            #+#    #+#             */
/*   Updated: 2023/02/08 01:36:11 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	how_many_args(char **str);
static char	*dup_w_quotes(char *str);
static int	how_many_flags(char **str);

t_to_exec	*get_args_w_flags_and_paths(char **splits, char **envp)
{
	t_to_exec	*to_exec;
	int			i;
	int			j;
	char		space;
	char		*tmp;
	char		quote;
	int			k;

	space = ' ';
	i = 0;
	j = 0;
	tmp = NULL;
	to_exec = calloc(sizeof(char **), how_many_args(splits));
	if (!to_exec)
		return (NULL);
	i = 0;
	while (splits[i + 1])
	{
		to_exec[j].cmd = calloc(sizeof(char *), 1 + how_many_flags(&splits[i])
				+ 1);
		if (!to_exec[j].cmd)
		{
			// free_to_exec(to_exec, j); // a implementer
			return (NULL);
		}
		i++;
		to_exec[j].path = get_path(to_exec[j].cmd[0], envp);
		k = 1;
		while (splits[i] && splits[i][0] == '-')
		{
			to_exec[j].cmd[k] = splits[i];
			i++;
			k++;
		}
		j++;
	}
	i = 0;
	return (to_exec);
}

static char	*dup_w_quotes(char *str)
{
	char		*res;
	char		*tmp;
	const char	*quote;

	quote = "\"";
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

static int	how_many_flags(char **str)
{
	int	i;

	i = 1;
	while (str[i] && str[i][0] == '-')
		i++;
	return (i - 1);
}
