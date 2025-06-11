#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/stat.h>

# define FOREVER	1
# define GREEN		"\033[0;32m"
# define RED		"\033[0;31m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define AQUA		"\033[0;36m"
# define RESET		"\033[0m"

typedef enum e_ttype
{
	T_DATA,
	T_PIPE,
	T_REDIRECT_IN,  // <
	T_REDIRECT_OUT, // >
	T_APPEND,		// >>
	T_HEREDOC,		// <<
}	t_ttype;

typedef enum e_qtype
{
	NO_Q,
	SINGLE_Q,
	DOUBLE_Q,
}	t_qtype;

typedef struct	s_ints
{
	int	start;
	int	end;
}	t_ints;

typedef struct	s_pipe
{
	int		pipes[2];
	int		prev_fd;
	pid_t	pid;
}	t_pipe;


typedef struct s_token
{
	char			*data;
	t_ttype			type;
	t_qtype			quote_type;
	struct s_token	*next;
}	t_token;

typedef struct s_env_list
{
	char				*key;
	char				*data;
	int					len;
	int					exported;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_expand
{
	t_env_list	*env_lst;
	char		*result;
	char		type;
	char		*var_name;
	char		*value;
	int			i;
	int			start;
	int			status;
	char		**args;
	int 		is_redirection_context;
	int 		ambiguous_redirect;
}	t_expand;


typedef struct s_command
{
	char				**av;
	char				*in_file;
	char				*out_file;
	char				**here_arr;
	int					in_fd;
	int					out_fd;
	int					pipe;
	int					heredoc;
	int					append;
	int					is_builtin;
	int					status;
	struct s_command	*next;
}	t_command;

// lexer functions
t_token		*handle_command(char *command, int *status);
int			add_to_list(char *command, t_ints ints, t_token **tokens_list, t_qtype q_type);
int			handle_token(char *command, int *i, t_token **tokens_list);
int			is_operator(char c);
int			check_operator(char *command, int start, t_token **tokens_list);
t_token		*new_token(char	*data, t_ttype t_type, t_qtype q_type);
t_ttype		token_type(char *data);
void		tokens_add_back(t_token **tokens_list, t_token *token);
int			handle_combined_token(char *cmd, int i, t_token **tokens_list);
int			is_space_or_operator(char c);
int			is_redirect(t_ttype type);
int			valid_command(t_token *tokens, int *status);
int			check_tokens(t_token *tokens_list);


// quotes functions
int			good_quotes(char *command);
int			handle_quotes(char *command, int start, t_token **tokens_list);
t_qtype		quote_type(char q);

// parse functions
t_command	*parse_tokens(t_token *tokens, t_env_list *env, int *status);
t_command	*cmd_create(int status);
void		cmds_add_back(t_command **cmds_list, t_command *cmd);
int			copy_av(t_command *cmd, char **new_av, int *i);
int			set_here_arr(t_command *cmd, char *del);
int			set_write_operator(t_command *cmd, t_token *tokens);


// env functions
t_env_list	*create_env_list(char **env);
t_env_list	*init_env(char *str, int status);
void		env_add_back(t_env_list **lst, t_env_list *env);

// expander functions //abeer
void		expand_braced_variable(char *data, t_expand *ex);
void		expand_status_variable(t_expand *ex);
void		expand_positional_parameter(char *data, t_expand *ex);
void		expand_named_variable(char *data, t_expand *ex);
void		handle_dollar(char *data, t_expand *ex);
char		*ft_strjoin_and_free(char *s1, char *s2);
char		*get_positional_value(char *num_str, char **args, int status);
char		*get_env_value(char *var_name, t_env_list *env);
void		append_char_to_result(char *data, t_expand *ex);
void		handel_s_q(char *data, t_expand *ex);
void		handel_d_q(char *data, t_expand *ex);
void		do_expand(char *data, t_expand *ex);
char		*expander(char *data, t_env_list *env_lst, int status, char **args);
void		expand_dollar_with_digits(char *data, t_expand *ex);
int 		contains_whitespace(const char *str);
void		setup_expand(t_expand *ex, t_env_list *env, int status, char **args);

// execution function
int			execute_command(t_command *cmd_list, int *status, t_env_list **env);
int			execute_builtin(t_command *cmd, int status, t_env_list **env);
void		waiting(int *status);
int			starting_exec(t_command *cmd_list, int *status, t_env_list **env);
void		handle_no_pipe_cmd(t_command *cmd_list, int *status, t_env_list **env);
int			check_found_command(t_command *cmd, int *status, t_env_list **env);
void		handle_child_cmd(t_command *cmd, int *status, t_env_list **env, int *std);


// builtin commands functions
int			handle_env(t_env_list **env);
int			handle_export(t_command *cmd, t_env_list **env);
t_env_list	*init_special_env(char *str, int status);
void		print_export(t_env_list **env);
int			ft_strchr_i(const char *s, int c);
int			valid_export(char *cmd);
int			new_export(char *cmd, t_env_list **env, int exp);
int			check_export_format(char *cmd);
int			handle_unset(t_command *cmd, t_env_list **env);
int			handle_cd(char **cmd, t_env_list **env);
int			count_av(char **str);
char		*get_home_path(t_env_list **env);
int			handle_exit(t_env_list **env, t_command **cmd, int status);
void		update_pwd_data(t_env_list *pwd, t_env_list *old_pwd);
void		handle_oldpwd(t_env_list **env, t_env_list **old_pwd);
int 		handle_echo(char **cmd);
int			handle_pwd(void);

// external commands
int			execute_external(t_command *cmd, t_env_list **env);
int			add_envs(t_env_list *env, char **envp);
int			env_len(t_env_list *env);
char		**env_list_to_array(t_env_list **env);
void		free_paths(char **paths);
char		*get_env_path(t_env_list *env);
int			handle_child_process(t_command *cmd, char *path, char **envp);
int			handle_parent_process(int pid, char *path, char **envp);
char		*get_cmd_path(char *cmd, t_env_list **env);
int			external_error(char *path, char **envp);

// redirections
int			open_heredocs(t_command *cmd, t_env_list *env, int *status);
int			redirect_fds(t_command *cmd);
void		reset_stds(int *std);
int			need_redirect(t_command *cmd);
int			write_fd_error(char *file);


// frees functions
void		free_tokens(t_token **tokens_list);
void		free_env_list(t_env_list **env);
void		free_av(char **s);
void		free_commands(t_command **cmds);
void		error_exit(int status, t_token **tokens, t_command **cmds, t_env_list **env);
void		exit_expand_error(char *cmd, t_env_list **env, t_expand **ex);



#endif
