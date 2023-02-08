/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:19:25 by alevra            #+#    #+#             */
/*   Updated: 2023/02/08 01:35:47 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_to_exec	*get_args_w_flags_and_paths(char **splits, char **envp);
void	coucou(int argc, char **argv, char **envp, int file_fd[2]);

int	main(int argc, char **argv, char **envp)
{
	int	file_fd[2];
	int	fd_file1;
	int	fd_file2;

	fd_file1 = open(argv[1], O_RDONLY);
	if (fd_file1 < 0)
		return (ft_printf("Could not open argv[1]\n"), -1);
	fd_file2 = open(argv[argc - 1], O_WRONLY | O_CREAT, 644);
	if (fd_file2 < 0)
		return (close(fd_file1), ft_printf("Could not open argv[5](%s)\n", //mettre un perror
				argv[5]), -2);
	file_fd[FILE_1] = fd_file1;
	file_fd[FILE_2] = fd_file2;
	coucou(argc - 3, argv, envp, file_fd);
	return (0);
}

void	coucou(int nb_cmd, char **argv, char **envp, int file_fd[2])
{
	int		pipe_fd[2];
	int		cmd_counter;
	int		status;
	int		pid;
	int		i;
	t_to_exec	*to_exec;
	char	*path_w_cmd;

	ft_printf("\n\nnb_cmd : %d\n\n", nb_cmd); //debug
	pipe(pipe_fd);
	to_exec = (get_args_w_flags_and_paths(&argv[2], envp));
	i = 0;
	cmd_counter = 0;
	while (to_exec[cmd_counter].cmd)
	{
		ft_printf("(parent) forking a child for cmd : %s\n",
				to_exec[cmd_counter].cmd);
		pid = fork();
		if (pid == 0)
		{
			if (cmd_counter == 0)
				child_process(to_exec[cmd_counter], envp, file_fd[FILE_1],
						pipe_fd[WRITE]);
			if (cmd_counter == 1)
				child_process(to_exec[cmd_counter], envp, pipe_fd[READ],
						file_fd[FILE_2]);
		}
		waitpid(pid, NULL, 0);
		cmd_counter++;
	}
}
