#include "../minishell.h"

int	set_operator(t_command *cmd, t_token *tokens)
{
	if (tokens->type == T_REDIRECT_IN)
	{
		if (cmd->in_file)
			free(cmd->in_file);
		cmd->in_file = ft_strdup(tokens->next->data);
		if (!cmd->in_file)
			return (0);
	}
	else if (tokens->type == T_HEREDOC)
	{
		if (!set_here_arr(cmd, tokens->next->data))
			return (0);
		cmd->heredoc = 1;
	}
	else if (tokens->type == T_REDIRECT_OUT || tokens->type == T_APPEND)
	{
		if (!set_write_operator(cmd, tokens))
			return (0);
	}
	return (1);
}

int	check_builtin(char *s)
{
	int			len;
	int			i;
	static char	*b_ins[] = {"echo", "cd", "pwd", "export",
		"unset", "env", "exit", NULL};

	if (!s || !*s)
		return (0);
	i = 0;
	while (b_ins[i])
	{
		len = ft_strlen(s);
		if (!ft_strncmp(s, b_ins[i], len))
			return (1);
		i++;
	}
	return (0);
}

int	set_av(t_command *cmd, char *data)
{
	char	**new_av;
	int		i;

	i = 0;
	while (cmd->av && cmd->av[i])
		i++;
	new_av = malloc(sizeof(char *) * (i + 2));
	if (!new_av)
		return (0);
	if (!copy_av(cmd, new_av, &i))
		return (0);
	new_av[i] = ft_strdup(data);
	if (!new_av[i])
	{
		free_av(new_av);
		return (0);
	}
	new_av[i + 1] = NULL;
	cmd->av = new_av;
	return (1);
}

int	process_token(t_command **new_cmd, t_command **cmds, t_token *tokens)
{
	t_command	*cmd;
	int			i;

	i = 0;
	if (tokens->type == T_PIPE)
	{
		(*new_cmd)->pipe = 1;
		cmd = cmd_create((*new_cmd)->status);
		if (!cmd)
			return (0);
		(*new_cmd) = cmd;
		cmds_add_back(cmds, (*new_cmd));
		i = 1;
	}
	else if (tokens->type == T_DATA)
	{
		i = set_av((*new_cmd), tokens->data);
		(*new_cmd)->is_builtin = check_builtin((*new_cmd)->av[0]);
	}
	else
	{
		i = set_operator((*new_cmd), tokens);
		tokens = tokens->next;
	}
	return (i);
}

t_command	*parse_tokens(t_token *tokens, t_env_list *env, int *status)
{
	t_token		*tmp_tokens;
	t_command	*cmds;
	t_command	*new_cmd;

	cmds = NULL;
	tmp_tokens = tokens;
	new_cmd = cmd_create(*status);
	if (!new_cmd)
		error_exit(1, &tokens, &cmds, &env);
	cmds_add_back(&cmds, new_cmd);
	while (tmp_tokens)
	{
		if (!process_token(&new_cmd, &cmds, tmp_tokens))
			error_exit(1, &tokens, &cmds, &env);
		if (tmp_tokens->type != T_DATA && tmp_tokens->type != T_PIPE)
			tmp_tokens = tmp_tokens->next->next;
		else
			tmp_tokens = tmp_tokens->next;
	}
	return (cmds);
}
