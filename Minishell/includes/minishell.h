/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modembel <modembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:47:04 by modembel          #+#    #+#             */
/*   Updated: 2025/03/15 19:03:35 by modembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell.h"
# include "stdio.h"
# include "stdlib.h"
# include "string.h"
# include "unistd.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>

# define FILE_NAME 0
# define INPUT 1
# define HEREDOC 2
# define TRUNC 3
# define APPEND 4
# define PIPE 5
# define CMD 6
# define ARG 7
# define VAR 8

extern volatile sig_atomic_t	g_exit_codes;

typedef struct s_data			t_data;

enum							e_quote
{
	SQUOTE,
	DQUOTE,
	NQUOTE,
};

typedef struct s_env
{
	char						*str;
	bool						free;
	bool						hide;

	struct s_env				*next;
	struct s_env				*prev;

}								t_env;

typedef struct s_cmd
{
	t_data						*data;

	int							infile;
	int							outfile;
	char						**param;
	int							fd[2];

	struct s_cmd				*next;
	struct s_cmd				*prev;

}								t_cmd;

typedef struct s_token
{
	char						*str;
	int							type;
	int							quote;

	struct s_token				*next;
	struct s_token				*prev;

}								t_token;

typedef struct s_data
{
	t_token						*token;
	t_cmd						*cmd;
	t_env						*envlist;

	pid_t						pid;

	bool						cancel;
	bool						env_unset;
	bool						end_quote;
	bool						skip_q;

	int							save_stdin;
	int							save_stdout;
	int							exit_code;
	char						*old_pwd;
	char						*pwd;
	char						*line;
	char						*home;
	char						**allcmd;
	char						**env;
	char						**tmps;

}								t_data;

void							ft_close(int fd);

// lexer_utils
bool							end_token(char *line, int i, bool quote);
t_token							*ft_last(t_token *token);
void							add_token(t_token **token, int type, char *s,
									int *i);
bool							is_space(char s);
bool							is_token(char s);
void							lexer_expander(t_token *token, char *line,
									t_data *data);

// expanser_utils
void							var_expansion(t_data *data);
void							set_var(t_token *token);
bool							check_var_char(char c);
void							set_var_range(int *start, int *end, char *str,
									int index);
char							*var_isolation(char *str, int index);
bool							var_in_env(char *str, t_env *env);
void							set_var_value(char **str, t_env *env,
									int index);
char							*before_dollar(char *str);
int								seconde_update_string(int *j, char *dest,
									char *replace, char *var);
void							clean_expansion(char *var, char *replace,
									char *copy);
int								env_size(char *str);
char							*copy_env(t_env *envi, char *var);
char							*update_string(char *str, char *replace,
									char *var, int index);
char							*special_cases(char *copy, char *var,
									int index);
void							set_var_valuee(char **str, t_env *env,
									int index, bool *skip);

// quote
bool							valide_dquote(char *str);
char							*quote_handler(char *str);
void							quote_destroyer(t_token *token);
void							set_quote(t_token *token);
bool							check_end(char *str, t_data *data);

// command_utils
bool							create_command(t_data *data);
t_cmd							*last_cmd(t_cmd *cmd);
void							add_cmd(t_cmd **cmd, t_data *data);
int								param_length(t_token *token);
bool							get_line(int fd, char *delimiter, t_env *env,
									t_data *data);
int								set_heredoc(char *str, t_data *data);
char							**get_param(t_token *token);
void							init_heredoc(t_data *data);

// libft
int								ft_strncmp(char *s1, char *s2, int length);
char							*ft_strdup(char *src);
int								ft_strlen(char *str);
int								ft_isalnum(int c);
char							*ft_substr(char *s, unsigned int start,
									size_t len);
char							*ft_itoa(int n);
void							ft_putstr_fd(char const *s, int fd);
char							*ft_strjoin(char *s1, char *s2);
char							**ft_split(const char *str, char charset);
char							*ft_strchr(const char *s, int c);
void							*ft_calloc(size_t count, size_t size);

// export
void							init_env(char **arg, t_env **env);
void							update_env(t_env **env, int index, char *str);
int								var_exist(char *str, t_env **env);
t_env							*last_env(t_env *env);
void							add_env(t_env **env, char *str);

// builtins
int								export_all(t_cmd *cmd, t_data *data);
int								ft_pwd(t_cmd *cmd);
int								ft_env(t_cmd *cmd, t_data *data);
int								ft_echo(t_cmd *cmd);
int								ft_cd(t_cmd *cmd, t_data *data);
int								unset_all(t_cmd *cmd, t_data *data);
int								ft_exit(t_cmd *cmd, t_data *data);
char							*get_oldpwd(t_data *data);

// exec
int								exec(t_data *data, t_cmd *cmd);
char							*set_path_cmd(t_cmd *cmd, t_data *data,
									char ***path_env, char **command);
void							free_path_error(char **path_env, char *command,
									t_cmd *cmd, int exit_c);
int								start_builtins(t_data *data, t_cmd *cmd);
int								identifie_builtin(char *arg);
int								child_process(t_cmd *command, t_data *data);

void							close_fd(t_cmd *command, t_cmd *actual_fd);

char							*path_in_env(t_env *env);

// clean
void							free_all(t_data *data);
void							exit_shell(t_data *data, int ex_code,
									int ctrl_d);

char							**copy_arg_env(t_data *data);

// signal
void							set_signal(void);
void							child_signal(void);
void							set_signal_child(void);
void							set_signal_parent_exec(void);
void							set_signal_parent(void);
void							if_sigint(int sig);

#endif