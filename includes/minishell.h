/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:52:48 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/02 09:41:08 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define REDIRIN 1
# define REDIROUT 2
# define REDIRAPP 3
# define REDIRHRE 4
# define REPIPE 5
# define REAND 6
# define REOR 7

typedef struct s_command {
	int					redirection;
	char				**command;
	struct s_command	*next;
}	t_command;

char		*getprompt(void);
void		shell_exit(void);
char		**split_args(const char *line, int len);
int			checkredir(const char *line, int len);
t_command	*parse_seqcmds(const char *line);
int			execute_line(char *line);
int			isredir(const char c);
int			getcmdlen(const char *line, int *pos);

#endif