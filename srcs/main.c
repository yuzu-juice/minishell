/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:16:44 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/15 13:52:06 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_sig_flag;

static char	*get_input_line(void);

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argv;
	g_sig_flag = 0;
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
	{
		perror("signal");
		return (1);
	}
	if (argc != 1)
		return (0);
	while (1)
	{
		line = get_input_line();
		if (ft_strlen(line) != 0)
		{
			add_history(line);
			exec_cmd(envp, line);
		}
		free(line);
	}
	return (0);
}

static char	*get_input_line(void)
{
	int	stdout_copy;
	int	dev_null;
	char	*line;

	if (isatty(STDIN_FILENO))
		line = readline("minishell> ");
	else
	{
		stdout_copy = dup(STDOUT_FILENO);
		if (stdout_copy == -1)
			return (NULL);
		dev_null = open("/dev/null", O_WRONLY);
		if (dev_null == -1)
			return (NULL);
		dup2(dev_null, STDOUT_FILENO);
		close(dev_null);
		line = readline("");
		dup2(stdout_copy, STDOUT_FILENO);
		close(stdout_copy);
	}
	return (line);
}
