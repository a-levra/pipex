/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:19:25 by alevra            #+#    #+#             */
/*   Updated: 2023/02/07 00:15:19 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char		**get_args_w_flags(char **splits);
static char	*get_path(char *cmd, char **envp);
void		coucou(int argc, char **argv, char **envp, int file_fd[2]);

int	main(int argc, char **argv, char **envp)
{
	int	file_fd[2];
	int	fd_file1;
	int	fd_file2;

	// if (argc != 5)
	// return (ft_printf("pipex : not enough arg\n"), -1);
	fd_file1 = open(argv[1], O_RDONLY);
	if (fd_file1 < 0)
		return (ft_printf("Could not open argv[1]\n"), -1);
	fd_file2 = open(argv[4], O_WRONLY | O_CREAT, 644);
	if (fd_file2 < 0)
		return (close(fd_file1), ft_printf("Could not open argv[5](%s)\n",
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
	char	*cmd;
	int		status;
	int		pid;
	int		i;
	char	**args;
	char	*path_w_cmd;

	ft_printf("\n\nnb_cmd : %d\n\n", nb_cmd); //debug
	pipe(pipe_fd);
	args = (get_args_w_flags(&argv[2]));
	ft_printf("args[0] : %s\n", args[0]); //debug
	ft_printf("args[1] : %s\n", args[1]); //debug
	ft_printf("args[2] : %s\n", args[2]); //debug
	ft_printf("args[3] : %s\n", args[3]); //debug
	i = 0;
	cmd_counter = 0;
	while (args[cmd_counter + 1])
	{
		path_w_cmd = get_path(args[cmd_counter], envp); //todo faire ne sorte que ca fonctionne
		ft_printf("cmd : %d\n", cmd_counter); //debug
		ft_printf("(parent) forking a child for cmd : %s\n", args[cmd_counter]);
		pid = fork();
		if (pid == 0)
		{
			cmd = args[cmd_counter];
			if (cmd_counter == 0)
				child_process(nb_cmd, path_w_cmd, envp, file_fd[FILE_1],
						pipe_fd[WRITE]);
			if (cmd_counter == 1)
				child_process(nb_cmd, path_w_cmd, envp, pipe_fd[READ],
						file_fd[FILE_2]);
		}
		else
			waitpid(pid, NULL, 0);
		cmd_counter++;
	}
}

static char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path_w_slash;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path_w_slash = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path_w_slash, cmd);
		free(path_w_slash);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}
