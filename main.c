/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliskam <eliskam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:01:48 by emencova          #+#    #+#             */
/*   Updated: 2024/10/08 15:41:09 by eliskam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./src/exec/execute.h"

t_env	g_env;

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_env.exit_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	handle_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	initialize_shell(t_shell *shell, char **envp)
{
	shell->cmds = NULL;
	shell->mpid = getpid();
	env_init(envp, shell);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	char	*line;

	line = NULL;
	initialize_shell(&shell, envp);
	rl_bind_key('\t', 0);
	while (ac && av)
	{
		handle_signals();
		line = readline("minishell🔥$ ");
		if (!line)
			break ;
		if (*line)
			process_command_line(line, &shell);
		free(line);
	}
	cleanup_shell(&shell);
	return (g_env.exit_status);
}
