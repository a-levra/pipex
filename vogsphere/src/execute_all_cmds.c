/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_all_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:14:45 by alevra            #+#    #+#             */
/*   Updated: 2023/02/09 23:28:08 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void		case_first(t_to_exec to_exec, int pipes[OPEN_MAX][2], int i, \
				int fd_file_1);
static void		case_middle(t_to_exec to_exec, int pipes[OPEN_MAX][2], int i);
static void		case_last(t_to_exec to_exec, int pipes[OPEN_MAX][2], int i, \
				int fd_file_2);
static void		exit_routine(int pipes[OPEN_MAX][2], int files[2], \
				int pids[OPEN_MAX], int i);

int	execute_all_cmds(t_to_exec *cmds, int files[2])
{
	int	pipes[OPEN_MAX][2];
	int	pids[OPEN_MAX];
	int	i;

	i = 0;
	while (cmds[i].cmd)
	{
		if (pipe(pipes[i]) < 0)
			return (ft_printf("Failed to create pipes\n"), -1);
		pids[i] = fork();
		if (pids[i] < 0)
			return (ft_printf("Failed to fork\n"), -1);
		if (pids[i] == 0)
		{
			if (i == 0)
				case_first(cmds[i], pipes, i, files[FILE_1]);
			if (i != 0 && cmds[i + 1].cmd)
				case_middle(cmds[i], pipes, i);
			if (!cmds[i + 1].cmd)
				case_last(cmds[i], pipes, i, files[FILE_2]);
		}
		i++;
	}
	return (exit_routine(pipes, files, pids, i), free_cmd_tab(&cmds), 0);
}

static void	exit_routine(int pipes[OPEN_MAX][2], int files[2],
		int pids[OPEN_MAX], int i)
{
	close_pipes_and_file_fd(pipes, files, i);
	wait_all_child_proc(pids, i);
}

static void	case_first(t_to_exec to_exec, int pipes[OPEN_MAX][2], int i,
		int fd_file_1)
{
	close(pipes[i][READ]);
	if (fd_file_1 > 0)
		child_proc(to_exec, fd_file_1, pipes[i][WRITE]);
	close(pipes[i][WRITE]);
	exit(EXIT_FAILURE);
}

static void	case_middle(t_to_exec to_exec, int pipes[OPEN_MAX][2], int i)
{
	close(pipes[i][READ]);
	close(pipes[i - 1][WRITE]);
	child_proc(to_exec, pipes[i - 1][READ], pipes[i][WRITE]);
}

static void	case_last(t_to_exec to_exec, int pipes[OPEN_MAX][2], int i,
		int fd_file_2)
{
	close(pipes[i][WRITE]);
	close(pipes[i][READ]);
	close(pipes[i - 1][WRITE]);
	if (fd_file_2 > 0)
		child_proc(to_exec, pipes[i - 1][READ], fd_file_2);
	close(pipes[i - 1][READ]);
	exit(EXIT_FAILURE);
}
