/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:47:34 by alevra            #+#    #+#             */
/*   Updated: 2023/02/14 17:00:45 by alevra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	freepath(char **paths);
static char	*test_abs_or_rel_path(char *cmd);

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path_w_slash;
	char	*path;
	int		i;

	i = 0;
	if (!envp || !envp[0])
		return (NULL);
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (test_abs_or_rel_path(cmd));
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':'); // a proteger
	i = 0;
	while (paths[i])
	{
		path_w_slash = ft_strjoin(paths[i], "/"); // a proteger
		path = ft_strjoin(path_w_slash, cmd); // a proteger
		free(path_w_slash);
		if (access(path, F_OK) == 0)
			return (freepath(paths), free(paths), path);
		free(path);
		i++;
	}
	return (freepath(paths), free(paths), NULL);
}

static char	*test_abs_or_rel_path(char *path)
{
	if (access(path, F_OK) == 0)
		return (ft_strdup(path));
	return (NULL);
}

static void	freepath(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
}
