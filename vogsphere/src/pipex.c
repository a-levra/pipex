/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:19:25 by alevra            #+#    #+#             */
/*   Updated: 2023/02/16 17:16:20 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	check_args(int argc, char **argv);

int	main(int argc, char **argv, char **envp)
{
	int			files[2];
	t_to_exec	*cmds;

	ft_printf("BONUS : %d\n", BONUS); //debug
	if (check_args(argc, argv) < 0)
		return (-1);
	if (!ft_strequ(argv[1], "here_doc"))
	{
		files[FILE_1] = open(argv[1], O_RDONLY);
		if (files[FILE_1] < 0)
			perror(argv[1]);
	}
	files[FILE_2] = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (files[FILE_2] < 0)
		perror(argv[argc - 1]);
	cmds = (get_args_w_flags_and_paths(argv, envp));
	if (!cmds)
	{
		if (!ft_strequ(argv[1], "here_doc"))
			close(files[FILE_1]);
		return (close(files[FILE_2]), -1);
	}
	if (execute_all_cmds(cmds, files) < 0)
		return (-1);
	return (close(files[FILE_2]), 0);
}

static int	check_args(int argc, char **argv)
{
	if (argc != 5 && !BONUS)
		return (ft_printf("Incorrect number of args\n"), -1);
	if (argc < 5 || (ft_strequ(argv[1], "here_doc") && argc < 6))
		return (ft_printf("Not enough args\n"), -1);
	return (0);
}
