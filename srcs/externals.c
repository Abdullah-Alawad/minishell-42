#include "../minishell.h"

char	*get_cmd_if_direct_path(char *cmd)
{
	char	*path;

	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
	{
		path = ft_strdup(cmd);
		if (!path)
			return (NULL);
		return (path);
	}
	return (NULL);
}

char	*check_path(char *full, char *tmp, char *cmd)
{
	full = ft_strjoin(tmp, cmd);
	if (!tmp)
		return (NULL);
	free(tmp);
	if (access(full, X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

char	*find_path(char **paths, char *cmd, char *tmp, int index)
{
	char	*full;

	index = 0;
	full = NULL;
	while (paths[index])
	{
		tmp = ft_strjoin(paths[index], "/");
		if (!tmp)
			return (NULL);
		full = check_path(full, tmp, cmd);
		if (full)
			return (full);
		index++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, t_env_list **env)
{
	char	*path;
	char	**paths;
	char	*tmp;
	char	*full;
	int		i;

	tmp = NULL;
	i = 0;
	path = get_cmd_if_direct_path(cmd);
	if (path)
		return (path);
	path = get_env_path(*env);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	full = find_path(paths, cmd, tmp, i);
	free_paths(paths);
	return (full);
}

int	execute_external(t_command *cmd, t_env_list **env)
{
	int		pid;
	int		exit_code;
	char	*path;

	if (!cmd || !cmd->av || !cmd->av[0])
		return (1);
	path = get_cmd_path(cmd->av[0], env);
	if (!path)
	{
		printf("%s: command not found\n", cmd->av[0]);
		return (127);
	}
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
		handle_child_process(cmd, env, path);
	exit_code = handle_parent_process(pid, path);
	return (exit_code);
}

