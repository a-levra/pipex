/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:20:18 by alevra            #+#    #+#             */
/*   Updated: 2023/02/09 23:30:56 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef READ
#  define READ 0
# endif
# ifndef WRITE
#  define WRITE 1
# endif
# ifndef FILE_1
#  define FILE_1 0
# endif
# ifndef FILE_2
#  define FILE_2 1
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif
# include "../libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_to_exec
{
	char	**cmd;
	char	*path;
	char	**envp;
}			t_to_exec;

void		child_proc(t_to_exec to_exec, int to_read, int to_write);
char		*get_path(char *cmd, char **envp);
void		wait_all_child_proc(int *pids, int childs_counter);
void		close_pipes_and_file_fd(int pipes[OPEN_MAX][2], int files[2],
				int i);
void		free_cmd_tab(t_to_exec **cmds);
void		free_cmd_tab2(t_to_exec *cmds);
t_to_exec	*get_args_w_flags_and_paths(char **splits, char **envp);

#endif
