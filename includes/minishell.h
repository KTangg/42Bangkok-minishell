/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:52:48 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/08 18:09:09 by tratanat         ###   ########.fr       */
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
void		shell_exit(void);

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
void		built_printerr(char *cmd, char *arg);
void		set_environ(char *index, char *value);
void		add_environ(char *index, char *value, int size);
int			getarrsize(char **arr);

// Builtin Commands Prototypes
int			check_built(char **argv, char **envp);
int			cmd_env(char **argv, char **envp);
int			cmd_echo(char **argv, char **envp);
int			cmd_exit(char **argv);
int			cmd_cd(char **argv);

// Exec Helper
int			is_pipe(t_command *cmd);
int			is_logical(t_command *cmd);
int			is_redirection(t_command *cmd);
void		redir_exec(t_command *command_line, char **command);

// Redirection Prototype
void		redir_out(t_command *command_line, char **commamd);
void		redir_app(t_command *command_line, char **commamd);
void		redir_inp(t_command *command_line, char **commamd);
void		here_document(t_command *command_line, char **commamd);

// Pipe Prototype
void		redir_pipe(t_command *left_cmd, t_command *right_cmd);

// Section Command Prototype
void		section_execute(t_command *cmd_section);
t_command	**section_cmd(t_command *command_line);

#endif
