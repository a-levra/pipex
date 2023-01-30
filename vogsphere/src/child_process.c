/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:25:43 by alevra            #+#    #+#             */
/*   Updated: 2023/01/30 15:56:00 by alevra           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//to_read is linked to child stdin, and child stdout is linked to to_write
void	child_process(int argc, char *cmd, char **envp, int to_read, int to_write)
{
	int		x;
	char	*args[] = {"/bin/bash", "-c", cmd, (char*)0};

	ft_printf("(child) lets execute cmd : %s\n", cmd);
	dup2(to_read, STDIN_FILENO);
	dup2(to_write, STDOUT_FILENO);
	close(to_read);
	close(to_write);
	execve("/bin/bash", args, envp);
	exit ;
}
