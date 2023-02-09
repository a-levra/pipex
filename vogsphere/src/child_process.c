/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:25:43 by alevra            #+#    #+#             */
/*   Updated: 2023/02/08 22:12:59 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//´to_read' is linked to child ´stdin´, and child ´stdout´ is linked to ´to_write´
void	child_proc(t_to_exec	to_exec, char **envp, int to_read, int to_write)
{
	int		x;

	ft_printf("\t(child) lets execute cmd_path : [%s][%s]\n", to_exec.path, to_exec.cmd[0]);
	if (to_exec.cmd[1])
		ft_printf("to_exec.cmd[2] : %s\n", to_exec.cmd[2]); //debug
	dup2(to_read, STDIN_FILENO);
	dup2(to_write, STDOUT_FILENO);
	close(to_read);
	close(to_write);
	execve(to_exec.path, to_exec.cmd, envp);
	exit (EXIT_FAILURE);
}
