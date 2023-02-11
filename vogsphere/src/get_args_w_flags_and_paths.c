/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_w_flags_and_paths.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:52:16 by alevra            #+#    #+#             */
/*   Updated: 2023/02/11 16:39:01 by alevra           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	how_many_args(char **str);


/* 
BEHAVIOR EXAMPLE:

./pipex infile "cmd1" "cmd2 -flagcmd2" outfile (classic case aka hd = 0)
	- to_exec_tab size : how_many_args(&argv[2 + 0]) + 1 + 0 
	- to_exec_tab[0].cmd[0] = cmd1
	-                ...[1] = NULL
	- to_exec_tab[1].cmd[0] = cmd2
	-                   [1] = -flagcmd2
	-                   [2] = NULL
	- to_exec_tab[2].cmd[0] = NULL

./pipex here_doc DELIMITER "cmd1" "cmd2" outfile (here_doc case aka hd = 1)
	- to_exec_tab size :  how_many_args(&argv[2 + 1]) + 1 + 1 
	- to_exec_tab[0].cmd[0] = here_doc
	-                ...[1] = DELIMITER
	- to_exec_tab[1].cmd[0] = cmd1
	- to_exec_tab[2].cmd[0] = cmd2
	- to_exec_tab[3].cmd[0] = NULL
 */
t_to_exec	*get_args_w_flags_and_paths(char **argv, char **envp)
{
	t_to_exec	*to_exec_tab;
	int			i;
	int			hd;

	i = 0;
	hd = ft_strequ(argv[1], "here_doc");
	ft_printf("hd : %d\n", hd); //debug
	to_exec_tab = ft_calloc(how_many_args(&argv[2 + hd]) + 1 + hd, sizeof(t_to_exec));
	if (!to_exec_tab)
		return (NULL);
	if (hd)
	{
		to_exec_tab[0].cmd = ft_calloc(3, sizeof(char *)); // a proteger
		to_exec_tab[0].cmd[0] = ft_strdup("here_doc");
		ft_printf("to_exec_tab[0].cmd[0] : %s\n", to_exec_tab[0].cmd[0]); //debug
		to_exec_tab[0].cmd[1] = ft_strdup(argv[2]);
		to_exec_tab[0].path = ft_strdup("");
		to_exec_tab[0].envp = NULL;
	}
	i = 0 + hd;
	while (argv[i + 2 + 1])
	{
		to_exec_tab[i].cmd = ft_split(argv[i + 2], ' ');
		ft_printf("to_exec_tab[%d].cmd[0] : %s\n", i, to_exec_tab[i].cmd[0]); //debug
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
