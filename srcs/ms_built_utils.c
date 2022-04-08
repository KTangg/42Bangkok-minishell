/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_built_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:19:08 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/08 18:09:41 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_ms_vars	*g_ms_vars;

int	check_built(char **argv, char **envp)
{
	if (!ft_strcmp("env", argv[0]))
		return (cmd_env(argv, envp));
	else if (!ft_strcmp("echo", argv[0]))
		return (cmd_echo(argv, envp));
	else if (!ft_strcmp("cd", argv[0]))
		return (cmd_cd(argv));
	else if (!ft_strcmp("exit", argv[0]))
		return (cmd_exit(argv));
	return (1);
}
