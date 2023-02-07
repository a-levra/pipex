/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_w_flags_and_paths.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:52:16 by alevra            #+#    #+#             */
/*   Updated: 2023/02/07 16:23:35 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	how_many_args(char **str);
static char	*dup_w_quotes(char *str);

char	***get_args_w_flags_and_paths(char **splits, char **envp)
{
	char	***args;
	int		i;
	int		j;
	char	space;
	char	*tmp;
	char	quote;

	space = ' ';
	i = 0;
	j = 0;
	tmp = NULL;
	args = calloc(sizeof(char **), how_many_args(splits) + 1);
	if (!args)
		return (NULL);
	while (i < how_many_args(splits) + 1)
	{
		args[i] = calloc(sizeof(char *), 2);
		if (!args[i])
			return (ft_freetab((void **) args, i - 1), free(args), NULL);
		i++;
	}
	i = 0;
	while (splits[i])
	{
		args[j][CMD] = ft_strdup(splits[i]);
		i ++;
		args[j][PATH] = get_path(args[j][CMD], envp);
		ft_printf("\n\nargs[j][CMD] : %s\n", args[j][CMD]); //debug
		while (splits[i] && splits[i][0] == '-')
		{
			ft_printf("splits[i] : %s\n", splits[i]); //debug
			tmp = ft_strjoin(args[j][CMD], (const char *)&space);
			free(args[j]);
			args[j][CMD] = tmp;
			tmp = ft_strjoin(args[j][CMD], splits[i]);
			ft_printf("tmp : %s\n", tmp); //debug
			args[j][CMD] = tmp;
			ft_printf("args[j][CMD] : %s\n", args[j][CMD]); //debug
			i++;
		}
		// args[j][CMD] = dup_w_quotes(args[j][0]);
		ft_printf("args[j][CMD] : %s\n", args[j][CMD]); //debug
		ft_printf("args[j][PATH] : %s\n", args[j][PATH]); //debug
		j++;
	}
	args[j][0] = (char *)0;
	if (tmp)
		free(tmp);
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
