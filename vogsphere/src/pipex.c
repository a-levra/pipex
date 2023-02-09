/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:19:25 by alevra            #+#    #+#             */
/*   Updated: 2023/02/09 16:46:55 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_to_exec(t_to_exec **to_exec);

t_to_exec	*get_args_w_flags_and_paths(char **splits, char **envp);
void		coucou(int argc, char **argv, char **envp, int file_fd[2]);

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
		return (close(fd_file1), ft_printf("Could not open argv[5](%s)\n",
											//mettre un perror
											argv[5]),
				-2);
	file_fd[FILE_1] = fd_file1;
	file_fd[FILE_2] = fd_file2;
	coucou(argc - 3, argv, envp, file_fd);
	return (0);
}

void	coucou(int nb_cmd, char **argv, char **envp, int file_fd[2])
{
	int			pipe_1[2];
	int			pipe_2[2];
	int			pipes[2][2];
	int			status;
	int			pid;
	int			i;
	t_to_exec	*cmd_tab;
	char		*path_w_cmd;
	int			a;
	int			b;
	char		*buf;

	i = 0;
	ft_printf("\n\nnb_cmd : %d\n\n", nb_cmd); //debug
	cmd_tab = (get_args_w_flags_and_paths(&argv[2], envp));
	if (!cmd_tab)
		return ;
	if (nb_cmd == 1)
		return (child_proc(cmd_tab[i], envp, file_fd[FILE_1], file_fd[FILE_2]));
	pipe(pipes[0]);
	pipe(pipes[1]);
	// if (nb_cmd == 3)
	// {
	// 	while (i < 3)
	// 	{
	// 		pid = fork();
	// 		if (pid == 0 && i == 0)
	// 			child_proc(cmd_tab[i], envp, file_fd[FILE_1], pipes[0][WRITE]);
	// 		if (pid == 0 && i == 1)
	// 			child_proc(cmd_tab[i], envp, pipes[0][READ], pipes[1][WRITE]);
	// 		if (pid == 0 && i == 2)
	// 		{
	// 			close(pipes[0][WRITE]);
	// 			child_proc(cmd_tab[i], envp, pipes[1][READ], file_fd[FILE_2]);
	// 		}
	// 		i++;
	// 	}
	// 	return ;
	// }
	while (cmd_tab[i].cmd)
	{
		ft_printf("(parent) forking a child for cmd : %s\n", cmd_tab[i].cmd[0]);
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
			{
				ft_printf("Writing in pipes[%d]\n", i % 2);
				close(pipes[i % 2][READ]);
				child_proc(cmd_tab[i], envp, file_fd[FILE_1], pipes[i % 2][WRITE]);
			}
			if (i != 0 && cmd_tab[i + 1].cmd)
			{
				ft_printf("Reading pipes[%d], Writing in pipes[%d]\n", i % 2 == 0, i % 2);
				close(pipes[i % 2][READ]);
				close(pipes[i % 2 == 0][WRITE]);
				child_proc(cmd_tab[i], envp, pipes[i % 2 == 0][READ], pipes[i % 2][WRITE]);
			}
			if (!cmd_tab[i + 1].cmd)
			{
				ft_printf("Reading pipes[%d]\n", i % 2 == 0);
				child_proc(cmd_tab[i], envp, pipes[i % 2 == 0][READ], file_fd[FILE_2]);
			}
		}
		waitpid(pid, NULL, 0);
		i++;
	}
	a = 0;
	while (cmd_tab[a].cmd != NULL)
	{
		b = 0;
		while (cmd_tab[a].cmd[b])
			free(cmd_tab[a].cmd[b++]);
		free(cmd_tab[a].cmd);
		free(cmd_tab[a++].path);
	}
	free(cmd_tab); //debug
	return ;        //debug
}

static void	free_to_exec(t_to_exec **cmd_tab)
{
}
