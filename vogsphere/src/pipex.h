/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:20:18 by alevra            #+#    #+#             */
/*   Updated: 2023/02/09 13:29:11 by alevra           ###   ########.fr       */
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
# include "../libft/libft.h"
# include <sys/wait.h>

typedef struct s_to_exec
{
	char		**cmd;
	char		*path;
}					t_to_exec;

void	child_proc(t_to_exec	to_exec, char **envp, int to_read, int to_write);
char	*get_path(char *cmd, char **envp);


#endif
