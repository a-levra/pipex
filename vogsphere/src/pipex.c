/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:19:25 by alevra            #+#    #+#             */
/*   Updated: 2023/01/25 01:58:15 by alevra           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	pid;
	int	fd[2];
	int	fd_file1;
	int	fd_file2;
	int	i;

	i = 0;
	pipe(fd);
	fd_file1 = open(argv[1], O_RDONLY); // if not ,,, error
	fd_file2 = open(argv[4], O_WRONLY | O_CREAT, 644);
	argc--;
	while (i <= argc -3)
	{
		ft_printf("(parent) forking a child for cmd : %s\n", argv[i+2]);
		pid = fork();
		if (pid == 0 && i == 0)
			child_process(argc, argv[i+2], envp, fd_file1, fd[WRITE]);
		if (pid == 0 && i == 1)
			child_process(argc, argv[i+2], envp, fd[READ], fd_file2);
		ft_printf("(parent) done executing i : %d\n", i);
		i++;
	}
	return (0);
}