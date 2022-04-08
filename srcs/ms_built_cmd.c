/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_built_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:38:26 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/09 06:25:24 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_ms_vars	*g_msvars;

int	cmd_echo(char **argv, char **envp)
{
	int	i;
	int	nonl;

	(void)envp;
	i = 1;
	nonl = 0;
	if (!argv[1])
		printf("\n");
	if (!argv[1])
		return (0);
	if (!ft_strcmp(argv[1], "-n"))
		nonl = 1;
	if (!argv[2] && nonl == 1)
		printf("\n");
	if (!argv[2] && nonl == 1)
		return (0);
	while (argv[i])
	{
		printf("%s", argv[i++]);
		if (argv[i])
			printf(" ");
	}
	if (!nonl)
		printf("\n");
	return (0);
}

int	cmd_env(char **argv, char **envp)
{
	int	i;

	(void)envp;
	i = 0;
	if (argv[1])
	{
		built_printerr(argv[0], argv[1]);
		return (-1);
	}
	else
	{
		while (g_msvars->environ[i])
			printf("%s\n", g_msvars->environ[i++]);
		return (0);
	}
}

int	cmd_pwd(char **argv)
{
	char	*str;

	if (argv[1])
	{
		built_printerr(argv[0], argv[1]);
		return (-1);
	}
	str = getvar("PWD");
	if (!str)
		return (-1);
	printf("%s\n", str);
	return (0);
}

int	cmd_cd(char **argv)
{
	int		err;
	char	*str;

	str = NULL;
	if (!argv[1])
	{
		str = getvar("HOME");
		chdir(str);
		setvar("PWD", str, g_msvars->env_lst);
		free(str);
		return (0);
	}
	if (argv[2])
		built_printerr(argv[0], argv[2]);
	if (argv[2])
		return (-1);
	err = chdir(argv[1]);
	if (err)
		perror(strerror(err));
	if (err)
		return (-1);
	str = getcwd(str, 0);
	setvar("PWD", str, g_msvars->env_lst);
	free(str);
	return (0);
}

int	cmd_exit(char **argv)
{
	if (argv[1])
	{
		built_printerr(argv[0], argv[1]);
		return (-1);
	}
	else
		shell_exit();
	return (0);
}
