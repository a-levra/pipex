/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_w_flags_and_paths.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:52:16 by alevra            #+#    #+#             */
/*   Updated: 2023/02/08 21:55:29 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	how_many_args(char **str);
static char	*dup_w_quotes(char *str);
static int	how_many_flags(char **str);

t_to_exec	*get_args_w_flags_and_paths(char **splits, char **envp)
{
	t_to_exec	*to_exec_tab;
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
	ft_printf("how_many_args(splits) : %d\n", how_many_args(splits)); //debug
	to_exec_tab = ft_calloc(how_many_args(splits) + 1, sizeof(t_to_exec));
	if (!to_exec_tab)
		return (NULL);
	i = 0;
	while (splits[i + 1])
	{
		to_exec_tab[j].cmd = ft_calloc(how_many_flags(&splits[i]) + 2, sizeof(char **));
		if (!to_exec_tab[j].cmd)
		{
			// free_to_exec(to_exec, j); // a implementer
			return (NULL);
		}
		to_exec_tab[j].cmd[0] = ft_strdup(splits[i]);
		ft_printf("to_exec_tab[j].cmd[0] : %s\n", to_exec_tab[j].cmd[0]); //debug
		i++;
		k = 1;
		while (splits[i] && splits[i][0] == '-')
		{
			to_exec_tab[j].cmd[k] = ft_strdup(splits[i]);
			ft_printf("to_exec_tab[j].cmd[k] : %s\n", to_exec_tab[j].cmd[k]); //debug
			i++;
			k++;
		}
		to_exec_tab[j].path = get_path(to_exec_tab[j].cmd[0], envp);
		j++;
	}
	return (to_exec_tab);
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
