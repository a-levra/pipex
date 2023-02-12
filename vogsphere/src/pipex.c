/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:19:25 by alevra            #+#    #+#             */
/*   Updated: 2023/02/12 23:25:16 by alevra           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute_all_cmds(t_to_exec *cmds, int files[2]);

int	main(int argc, char **argv, char **envp)
{
	int			files[2];
	t_to_exec	*cmds;

	if (argc < 4)
		return (ft_printf("Not enough args\n"), -1);
	if (!ft_strequ(argv[1], "here_doc"))
	{
		files[FILE_1] = open(argv[1], O_RDONLY);
		if (files[FILE_1] < 0)
			perror(argv[1]);
	}
	files[FILE_2] = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 644);
	if (files[FILE_2] < 0)
		perror(argv[argc - 1]);
	cmds = (get_args_w_flags_and_paths(argv, envp));
	if (!cmds)
		return (ft_printf("Errors while parsing the commands\n"), 0);
	if (execute_all_cmds(cmds, files) < 0)
		return (-1);
	return (0);
}

