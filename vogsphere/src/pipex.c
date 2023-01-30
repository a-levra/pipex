/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:19:25 by alevra            #+#    #+#             */
/*   Updated: 2023/01/30 15:59:29 by alevra           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	coucou(int argc, char**argv, char **envp, int file_fd[2]);

int	main(int argc, char **argv, char **envp)
{
	int	file_fd[2];
	int	fd_file1;
	int	fd_file2;

	if (argc != 5)
		return (ft_printf("pipex : not enough arg\n"), -1);
	fd_file1 = open(argv[1], O_RDONLY);
	if (fd_file1 < 0)
		return (ft_printf("Could not open argv[1]\n"), -1);
	fd_file2 = open(argv[4], O_WRONLY | O_CREAT, 644);
	if (fd_file2 < 0)
		return (close(fd_file1), ft_printf("Could not open argv[2]\n"), -2);
	file_fd[FILE_1] = fd_file1;
	file_fd[FILE_2] = fd_file2;
	coucou(--argc, argv, envp, file_fd);
	return (0);
}

void	coucou(int argc, char**argv, char **envp, int file_fd[2])
{
	int	pipe_fd[2];
	int	i;
	int	pid;

	pipe(pipe_fd);
	i = 0;
	while (i <= argc -3)
	{
		ft_printf("(parent) forking a child for cmd : %s\n", argv[i + 2]);
		pid = fork();
		if (pid == 0 && i == 0)
			child_process(argc, argv[i + 2], envp, file_fd[FILE_1], pipe_fd[WRITE]);
		// if (milieu)
		// 	child_process(argc, argv[i + 2], envp, pipe_fd[READ],  pipe_fd[WRITE]);	
		if (pid == 0 && i == 1)
			child_process(argc, argv[i + 2], envp, pipe_fd[READ], file_fd[FILE_2]);
		ft_printf("(parent) done executing i : %d\n", i);
		i++;
	}
}
