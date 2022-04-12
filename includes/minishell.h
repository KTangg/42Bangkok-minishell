/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:52:48 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/12 15:20:08 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <stdbool.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

// Define Redirection Code
# define REDIRIN 1
# define REDIROUT 2
# define REDIRAPP 3
# define REDIRHRE 4
# define REPIPE 5
# define REAND 6
# define REOR 7
# define HERE_DOCFILE "here_doc.txt"

// Outmode: 0 - Do nothing; 1 - '>' to file; 2 - '>>' to file;
// Inmode: 0 - Do nothing; 1 - '<' read from file; 2 - '<<' Here Document
typedef struct s_redirect {
	char				*file;
	int					redirect;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command {
	int					redirection;
	t_redirect			*output;
	t_redirect			*input;
	char				**command;
	int					recursive;
	struct s_command	*next;
	struct s_command	*next_pipe;
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

typedef struct s_parexcp {
	int	sq_open;
	int	dq_open;
	int	p_open;
	int	any_open;
}	t_parexcp;

char		*getprompt(void);

// Line Process Prototype
bool		shell_line(char *line);

// Execute Process Prototype
bool		execute_execve(char *argv[]);
bool		redir_execute(t_command *command_line);

// Split Process Prototype
char		**split_args(const char *line, int len);
int			checkredir(const char *line, int len);
t_command	*parse_seqcmds(char *line);
int			isredir(const char c);
int			getcmdlen(const char *line, int *pos, int *recursive);
t_ms_vars	*init_global(char **envp);
void		app_var(t_vars **lst, char *index, char *value);
void		print_varlist(t_vars **lst);
int			isquoting(char c, t_parexcp *p);
char		*expand_var(char *line);
int			validvarn(char c, int pos);
t_command	*checkcmdlst(t_command *cmdlist);
void		setvar(char *index, char *value, t_vars **lst);
int			isvarset(char *cmd);
char		**lst_delcmd(t_command *cmdlist, char *cmd);
t_command	*lst_cmdfile(t_command *cmdlst, t_command *cur);
char		*getvar(char *index);
void		print_cmdlst(t_command *cmdlist);
void		print_synterr(const char *str);
char		*getshell(void);
void		setshell(char *name);
void		parsevarset(char *cmd, t_vars **lst);
void		unsetvar(char *index);
void		init_parexcp(t_parexcp *p);
void		ms_cleanup_global(void);
void		init_cmd(t_command *cmd);
void		clean_cmdfiles(t_redirect *target);

// Exec Helper
bool		check_execute(t_command *command_line);
t_command	*reverse_command(t_command *command_line);
t_redirect	*reverse_redirect(t_redirect *redirect);

// Redirection Prototype
int			redir_out(char *path);
int			redir_app(char *path);
int			redir_inp(char *path);
int			here_document(char *end);

// Pipe | Operation Prototype
bool		redir_pipe(t_command *left_cmd, t_command *right_cmd);

// And && Operation Prototype
bool		redir_and(t_command *left_cmd, t_command *right_cmd);

// Or || Operation Prototype
bool		redir_or(t_command *left_cmd, t_command *right_cmd);

// Section Command Prototype
bool		section_execute(t_command *cmd_section);
bool		section_list(t_command *cmd_list);

#endif
