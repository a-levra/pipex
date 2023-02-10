/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:06:50 by alevra            #+#    #+#             */
/*   Updated: 2023/02/09 23:30:36 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_all_child_proc(int *pids, int childs_counter)
{
	int	k;

	k = 0;
	while (k < childs_counter)
		waitpid(pids[k++], NULL, 0);
}

void	close_pipes_and_file_fd(int pipes[OPEN_MAX][2], int files[2], int i)
{
	int	k;

	k = 0;
	while (k < i)
	{
		close(pipes[k][READ]);
		close(pipes[k][WRITE]);
		k++;
	}
	close(files[FILE_1]);
	close(files[FILE_1]);
}

void	free_cmd_tab(t_to_exec **cmds)
{
	free_cmd_tab2(*cmds);
	free(*cmds);
}

void	free_cmd_tab2(t_to_exec *cmds)
{
	int	a;
	int	b;

	a = 0;
	while (cmds[a].cmd != NULL)
	{
		b = 0;
		while (cmds[a].cmd[b])
			free(cmds[a].cmd[b++]);
		free(cmds[a].cmd);
		free(cmds[a++].path);
	}
}
