/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_built_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:12:58 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/09 07:20:15 by tratanat         ###   ########.fr       */
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
