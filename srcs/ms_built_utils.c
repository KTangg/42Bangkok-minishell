/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_built_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:19:08 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/21 07:53:45 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	mov_var(char *name);

extern t_ms_vars	*g_msvars;

int	is_builtin(char **cmdchain)
{
	char	*cmd;

	cmd = cmdchain[0];
	if (!cmd)
		return (0);
	if (!ft_strcmp("env", cmd))
		return (1);
	else if (!ft_strcmp("echo", cmd))
		return (1);
	else if (!ft_strcmp("cd", cmd))
		return (1);
	else if (!ft_strcmp("unset", cmd))
		return (1);
	else if (!ft_strcmp("export", cmd))
		return (1);
	else if (!ft_strcmp("pwd", cmd))
		return (1);
	else if (!ft_strcmp("exit", cmd))
		return (1);
	else if (!ft_strcmp("ls", cmd))
		return (1);
	return (0);
}

int	execute_built(char **argv)
{
	char	**envp;

	envp = g_msvars->environ;
	if (!argv || !(*argv))
		return (0);
	if (!ft_strcmp("env", argv[0]))
		return (cmd_env(argv, envp));
	else if (!ft_strcmp("echo", argv[0]))
		return (cmd_echo(argv, envp));
	else if (!ft_strcmp("cd", argv[0]))
		return (cmd_cd(argv));
	else if (!ft_strcmp("unset", argv[0]))
		return (cmd_unset(argv));
	else if (!ft_strcmp("export", argv[0]))
		return (cmd_export(argv));
	else if (!ft_strcmp("pwd", argv[0]))
		return (cmd_pwd(argv));
	else if (!ft_strcmp("exit", argv[0]))
		return (cmd_exit(argv));
	else if (!ft_strcmp("ls", argv[0]))
		return (cmd_ls(argv));
	return (1);
}

int	cmd_export(char **argv)
{
	int	i;

	i = 1;
	if (!argv[1])
		return (0);
	while (argv[i])
	{
		if (isvarset(argv[i]))
			parsevarset(argv[i], g_msvars->env_lst);
		else if (!check_varn(argv[i]))
			cmd_varerr(argv[0], argv[i]);
		else
			mov_var(argv[i]);
		i++;
	}
	return (0);
}

static void	mov_var(char *name)
{
	t_vars	*temp;

	temp = *(g_msvars->var_lst);
	while (temp && ft_strcmp(name, temp->index))
		temp = temp->next;
	if (temp == NULL)
		return ;
	setvar(temp->index, temp->value, g_msvars->env_lst);
	unsetvar(name, 2);
}

int	check_varn(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (!validvarn(name[i], i))
			return (0);
		i++;
	}
	return (1);
}
