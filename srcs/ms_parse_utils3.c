/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 11:15:44 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/08 14:27:32 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parexcp(t_parexcp *p)
{
	p->any_open = 0;
	p->sq_open = 0;
	p->dq_open = 0;
	p->p_open = 0;
}

void	init_cmd(t_command *cmd)
{
	cmd->recursive = 0;
	cmd->redirection = 0;
	cmd->next = NULL;
	cmd->output = NULL;
	cmd->input = NULL;
}
