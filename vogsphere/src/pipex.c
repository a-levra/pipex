/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:19:25 by alevra            #+#    #+#             */
/*   Updated: 2023/02/10 02:14:13 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int			execute_all_cmds(t_to_exec *cmds, int files[2]);

int	main(int argc, char **argv, char **envp)
{
	int			files[2];
	int			fd_file1;
	int			fd_file2;
	t_to_exec	*cmds;

	fd_file1 = open(argv[1], O_RDONLY);
	if (fd_file1 < 0)
		perror(argv[1]);
	fd_file2 = open(argv[argc - 1], O_WRONLY | O_CREAT, 644);
	if (fd_file2 < 0)
		perror(argv[argc - 1]);
	files[FILE_1] = fd_file1;
	files[FILE_2] = fd_file2;
	cmds = (get_args_w_flags_and_paths(&argv[2], envp));
	if (!cmds)
		return (ft_printf("Errors while parsing the commands\n"), 0);
	if (execute_all_cmds(cmds, files) < 0)
		return (-1);
	return (0);
}
