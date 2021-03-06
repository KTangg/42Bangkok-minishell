/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 18:04:16 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/22 13:15:32 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "minishell.h"

extern t_ms_vars	*g_msvars;

// Free env_array
static void	free_path_env(char **path_env)
{
	size_t	i;

	if (path_env == NULL)
		return ;
	i = 0;
	while (path_env[i] != NULL)
		free(path_env[i++]);
	free(path_env);
}

// Get path in environment variable
static char	**get_path_env(void)
{
	t_vars	*cursor;

	if (g_msvars->env_lst == NULL)
	{
		ft_putendl_fd("get path: cannot import environment", 2);
		return (NULL);
	}
	cursor = *(g_msvars->env_lst);
	if (cursor == NULL)
	{
		ft_putendl_fd("get path: empty environment", 2);
		return (NULL);
	}
	while (cursor != NULL)
	{
		if (ft_strcmp("PATH", cursor->index) == 0)
			break ;
		cursor = cursor->next;
	}
	if (cursor != NULL)
		return (ft_split(cursor->value, ':'));
	return (NULL);
}

// Join path with the command
static char	*path_join(char *prefix, char *suffix)
{
	char	*path;
	size_t	size;
	size_t	n_pre;
	size_t	n_suf;

	n_pre = ft_strlen(prefix);
	n_suf = ft_strlen(suffix);
	size = n_pre + n_suf + 2;
	path = (char *)malloc(sizeof(char) * size);
	if (path == NULL)
	{
		ft_putendl_fd("malloc: allocation failed", STDERR_FILENO);
		return (NULL);
	}
	ft_memcpy(path, prefix, n_pre);
	path[n_pre] = '/';
	ft_memcpy(&path[n_pre + 1], suffix, n_suf + 1);
	return (path);
}

// Checking access to file in every path
static char	*check_path(char *cmd)
{
	char	*path;
	char	**path_env;
	size_t	i;

	if (!access(cmd, F_OK) && !access(cmd, X_OK))
		return (ft_strdup(cmd));
	path_env = get_path_env();
	i = 0;
	while (path_env[i] != NULL)
	{
		path = path_join(path_env[i++], cmd);
		if (path == NULL)
			continue ;
		if (!access(path, F_OK) && !access(path, X_OK))
		{
			free_path_env(path_env);
			return (path);
		}
		free(path);
	}
	if (path_env != NULL)
		free_path_env(path_env);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	return (NULL);
}

// Find path and execute right executable file
int	execute_execve(char *argv[])
{
	int		status;
	pid_t	pid;
	char	*cmd;
	char	*path;

	cmd = argv[0];
	path = check_path(cmd);
	if (path == NULL)
		return (CMD_NOT_FOUND);
	pid = fork();
	if (pid < 0)
		return (FORK_FAIL);
	if (pid == 0)
	{
		g_msvars->fork++;
		execve(path, argv, g_msvars->environ);
		perror(path);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	free(path);
	return (WEXITSTATUS(status));
}
