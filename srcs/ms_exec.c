/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 18:04:16 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/02 11:01:54 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// Get path in environment variable
char	**get_path_env(void)
{
	char	**path_env;

	path_env = (char **)malloc(sizeof(char *) * 2);
	path_env[0] = "/usr/bin";
	path_env[1] = NULL;
	return (path_env);
}

// Join path with the command
char	*path_join(char *prefix, char *suffix)
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
		printf("malloc: Allocation error\n");
		return (NULL);
	}
	ft_memcpy(path, prefix, n_pre);
	path[n_pre] = '/';
	ft_memcpy(&path[n_pre + 1], suffix, n_suf + 1);
	return (path);
}

// Checking access to file in every path
char	*check_path(char *cmd)
{
	char	*path;
	char	**path_env;
	size_t	i;

	path_env = get_path_env();
	i = 0;
	while (path_env[i] != NULL)
	{
		path = path_join(path_env[i++], cmd);
		if (path == NULL)
			continue;
		if (!access(path, F_OK) && !access(path, X_OK))
		{
			free(path_env);
			return (path);
		}
		free(path);
	}
	printf("%s: command not found\n", cmd);
	free(path_env);
	return (NULL);
}

// Find path and execute right executable file
void	execute(char *argv[])
{
	pid_t	pid;
	char	*cmd;
	char	*path;

	cmd = argv[0];
	if (cmd == NULL)
		return ;
	path = check_path(cmd);
	if (path == NULL)
		return ;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		return ;
	}
	if (pid == 0)
	{
		execve(path, argv, NULL);
		perror(cmd);
	}
	free(path);
}
