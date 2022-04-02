/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:39:27 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/01 04:10:41 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Display input prompt in format username@hostname: current_working_directory
char	*getprompt(void)
{
	char	prompt[1000];
	char	cwd[1000];

	getcwd(cwd, 1000);
	ft_strlcpy(prompt, getenv("USER"), 1000);
	ft_strlcat(prompt, "@", 1000);
	ft_strlcat(prompt, getenv("NAME"), 1000);
	ft_strlcat(prompt, ":", 1000);
	if (!ft_strncmp(cwd, getenv("HOME"), ft_strlen(getenv("HOME"))))
	{
		ft_strlcat(prompt, "~", 1000);
		ft_strlcat(prompt, cwd + ft_strlen(getenv("HOME")), 1000);
	}
	else
		ft_strlcat(prompt, cwd, 1000);
	ft_strlcat(prompt, "$ ", 1000);
	return (ft_strdup(prompt));
}

int	execute_line(char *line)
{
	t_command	*cmdlist;
	t_command	*temp;
	int			i;
	int			j;
	t_command	*clean;

	i = 0;
	j = 0;
	cmdlist = parse_seqcmds(line);
	if (!cmdlist)
		return (-1);
	temp = cmdlist;
	while (temp)
	{
		printf("[Command %i] - ", i++);
		while ((temp->command)[j])
		{
			printf("[%i] %s ", j, (temp->command)[j]);
			free(temp->command[j]);
			j++;
		}
		free(temp->command);
		j = 0;
		printf(" - Redirection: %i\n", temp->redirection);
		clean = temp;
		temp = temp->next;
		free(clean);
	}
	return (0);
}