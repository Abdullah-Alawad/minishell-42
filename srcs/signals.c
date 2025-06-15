#include "../minishell.h"

volatile sig_atomic_t	g_s = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	g_s = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	ctrl_d(t_env_list **env, int status, int ac)
{
	(void)ac;
	ft_printf("exit\n");
	free_env_list(env);
	rl_clear_history();
	exit(status);
}
