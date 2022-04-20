/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_built_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:12:58 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/21 06:40:36 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_printerr(char *cmd, char *arg)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": invalid option -- \'", 2);
	if (arg[0] == '-')
		ft_putstr_fd(arg + 1, 2);
	else
		ft_putstr_fd(arg, 2);
	ft_putstr_fd("\'\n", 2);
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
