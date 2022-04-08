/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_built_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:19:08 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/08 20:36:33 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	mov_var(char *name);

extern t_ms_vars	*g_msvars;

int	check_built(char **argv, char **envp)
{
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
	else if (!ft_strcmp("exit", argv[0]))
		return (cmd_exit(argv));
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
	setvar(temp->index, temp->value, g_msvars->var_lst);
	unsetvar(name, 2);
}

void	cmd_varerr(char *cmd, char *arg)
{
	char	*shell;

	shell = getshell();
	ft_putstr_fd(shell, 2);
	free(shell);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
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
