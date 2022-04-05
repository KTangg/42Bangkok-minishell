/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:52:48 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/05 07:06:52 by tratanat         ###   ########.fr       */
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
# define HERE_DOCFILE "here_doc.txt"

// Outmode: 0 - Do nothing; 1 - > to file; 2 - >> to file;
typedef struct s_command {
	int					redirection;
	char				**command;
	char				*fileout;
	int					outmode;
	int					recursive;
	struct s_command	*next;
}	t_command;

typedef struct s_vars {
	char			*index;
	char			*value;
	struct s_vars	*next;
}	t_vars;

typedef struct s_ms_vars {
	int		exit_status;
	char	**environ;
	t_vars	**env_lst;
	t_vars	**var_lst;
}	t_ms_vars;

// Logic: 0 - Execute; 1 - AND; 2 - OR;
typedef struct s_cmdset {
	struct s_cmdset	*cmdset1;
	struct s_cmdset	*cmdset2;
	t_command		*command;
	int				logic;
}	t_cmdset;

char		*getprompt(void);

// Line Process Prototype
int			shell_line(char *line);

// Execute Process Prototype
void		execute(char *argv[]);

// Split Process Prototype
char		**split_args(const char *line, int len);
int			checkredir(const char *line, int len);
t_command	*parse_seqcmds(char *line);
int			isredir(const char c);
int			getcmdlen(const char *line, int *pos, int *recursive);
t_ms_vars	*init_global(char **envp);
void		app_var(t_vars **lst, char *line);
void		print_varlist(t_vars **lst);
int			isquoting(char c, int *sq_open, int *dq_open, int *p_open);
char		*expand_var(char *line);
int			validvarn(char c, int pos);
t_command	*checkcmdlst(t_command *cmdlist);
void		setvar(char *cmd);
int			isvarset(char *cmd);
char		**lst_delcmd(t_command *cmdlist, char *cmd);
t_command	*lst_cmdfile(t_command *cmdlst, t_command *cur);
char		*getvar(char *index);
void		print_cmdlst(t_command *cmdlist);

// Redirection Prototype
void		redir_out(t_command *command_line);
void		redir_app(t_command *command_line);
void		redir_inp(t_command *command_line);
void		here_document(t_command *command_line);

// Pipe Prototype
void		redir_pipe(t_command *command_line);

// Section Command Prototype
void		section_execute(t_command *cmd_section);
t_command	**section_cmd(t_command *command_line);

#endif
