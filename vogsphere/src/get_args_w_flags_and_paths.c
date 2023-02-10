/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_w_flags_and_paths.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:52:16 by alevra            #+#    #+#             */
/*   Updated: 2023/02/10 02:16:03 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	how_many_args(char **str);

t_to_exec	*get_args_w_flags_and_paths(char **splits, char **envp)
{
	t_to_exec	*to_exec_tab;
	int			i;

	i = 0;
	to_exec_tab = ft_calloc(how_many_args(splits) + 1, sizeof(t_to_exec));
	if (!to_exec_tab)
		return (NULL);
	i = 0;
	while (splits[i + 1])
	{
		to_exec_tab[i].cmd = ft_split(splits[i], ' ');
		to_exec_tab[i].path = get_path(to_exec_tab[i].cmd[0], envp);
		to_exec_tab[i].envp = envp;
		i++;
	}
	to_exec_tab[i].cmd = NULL;
	return (to_exec_tab);
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
