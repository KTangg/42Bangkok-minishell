/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 06:16:12 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/20 19:02:42 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_synterr(const char *str)
{
	char	*shell;

	shell = getshell();
	ft_putstr_fd(shell, 2);
	ft_putstr_fd(": syntax error near unexpected token `", 2);
	ft_putchar_fd(*str, 2);
	ft_putstr_fd("\'\n", 2);
	free(shell);
}

void	print_wilderr(const char *str)
{
	char	*shell;

	shell = getshell();
	ft_putstr_fd(shell, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd((char *)str, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	free(shell);
}
