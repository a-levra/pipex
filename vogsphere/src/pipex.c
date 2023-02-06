/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:19:25 by alevra            #+#    #+#             */
/*   Updated: 2023/02/02 17:40:32 by alevra           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_args_w_flags(char **splits);

void	coucou(int argc, char**argv, char **envp, int file_fd[2]);

int	main(int argc, char **argv, char **envp)
{
	int		file_fd[2];
	int		fd_file1;
	int		fd_file2;

	// if (argc != 5)
		// return (ft_printf("pipex : not enough arg\n"), -1);
	fd_file1 = open(argv[1], O_RDONLY);
	if (fd_file1 < 0)
		return (ft_printf("Could not open argv[1]\n"), -1);
	fd_file2 = open(argv[5], O_WRONLY | O_CREAT, 644);
	if (fd_file2 < 0)
		return (close(fd_file1), ft_printf("Could not open argv[2]\n"), -2);
	file_fd[FILE_1] = fd_file1;
	file_fd[FILE_2] = fd_file2;
	coucou(argc - 3, argv, envp, file_fd);
	return (0);
}

void	coucou(int nb_cmd, char**argv, char **envp, int file_fd[2])
{
	int		pipe_fd[2];
	int		cmd_counter;
	char	*cmd;
	int		status;
	int		pid;
	int		i;
	char	**args;
	
	ft_printf("nb_cmd : %d\n", nb_cmd); //debug
	pipe(pipe_fd);
	//todo trouver pourquoi le wc -l se transforme en wc-l
	args = (get_args_w_flags(&argv[2]));
	ft_printf("args[0] : %s\n", args[0]); //debug
	ft_printf("args[1] : %s\n", args[1]); //debug
	ft_printf("args[2] : %s\n", args[2]); //debug
	ft_printf("args[3] : %s\n", args[3]); //debug
	ft_printf("args[4] : %s\n", args[4]); //debug
	i = 0;	
	cmd_counter = 0;
	while (args[cmd_counter+1])
	{
		ft_printf("cmd : %d\n", cmd_counter); //debug
		ft_printf("(parent) forking a child for cmd : %s\n", args[cmd_counter]);
		pid = fork();
		if (pid == 0)
		{	
			ft_printf("\t(child) my pid is %d\n", getpid());
			cmd = args[cmd_counter];
			if (cmd_counter == 1)
				child_process(nb_cmd, cmd, envp, file_fd[FILE_1], pipe_fd[WRITE]);
			if (cmd_counter != 1 && cmd_counter != nb_cmd)
				child_process(nb_cmd, cmd, envp, pipe_fd[READ], pipe_fd[WRITE]);
			if (cmd_counter == nb_cmd)
				child_process(nb_cmd, cmd, envp, pipe_fd[READ], file_fd[FILE_2]);
		}
		else
		{
			waitpid(pid,NULL,0);
			// ft_printf("waited for %d (i : %d)\n",pid, i); //debug
		}
		cmd_counter++;
	}
}
