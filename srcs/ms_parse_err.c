/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 06:16:12 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/06 09:09:15 by tratanat         ###   ########.fr       */
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
