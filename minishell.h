#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

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

typedef struct s_token
{
	char			*data;
	t_ttype			type;
	t_qtype			quote_type;
	struct s_token	*next;
}	t_token;

typedef struct s_command
{
	char				**av;
	char				**here_arr;
	char				*in_file;
	char				*out_file;
	int					pipe;
	int					heredoc;
	int					append;
	int					is_builtin;
	int					status;
	struct s_command	*next;
}	t_command;	

typedef struct s_env_list
{
	char				*key;
	char				*data;
	int					len;
	int					exported;
	struct s_env_list	*next;
}	t_env_list;

// lexer functions
t_token		*handle_command(char *command, int *status);
int			add_to_list(char *command, t_ints ints, t_token **tokens_list, t_qtype q_type);
int			handle_token(char *command, int *i, t_token **tokens_list);
int			is_operator(char c);
int			check_operator(char *command, int start, t_token **tokens_list);

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

// env functions
t_env_list	*create_env_list(char **env);
t_env_list	*init_env(char *str, int status);
void		env_add_back(t_env_list **lst, t_env_list *env);


// expander functions
char		*expander(char *data, t_env_list *env, int status);

// execution function
void		execute_command(t_command *cmd_list, char *command, int *status, t_env_list **env);

// builtin commands functions
int			handle_env(t_env_list **env);
int			handle_export(t_command *cmd, t_env_list **env);
t_env_list	*init_special_env(char *str, int status);
void		print_export(t_env_list **env);
int			ft_strchr_i(const char *s, int c);
int			handle_unset(t_command *cmd, t_env_list **env);
int			handle_cd(char **cmd, t_env_list **env);
int			count_av(char **str);
char		*get_home_path(t_env_list **env);
int			handle_exit(t_env_list **env, t_command **cmd, int status);
void		update_pwd_data(t_env_list *pwd, t_env_list *old_pwd);
void		handle_oldpwd(t_env_list **env, t_env_list **old_pwd);

// frees functions
void		free_tokens(t_token **tokens_list);
void		free_env_list(t_env_list **env);
void		free_av(char **s);
void		free_commands(t_command **cmds);
void		error_exit(int status, t_token **tokens, t_command **cmds, t_env_list **env);



#endif