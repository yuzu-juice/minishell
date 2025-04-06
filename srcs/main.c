/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:16:44 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/06 14:17:18 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_sig_flag;

static void	minishell(t_env *env);
static void	minishell_loop(t_env *env);
static char	*get_input_line(void);

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argv;
	g_sig_flag = 0;
	if (argc != 1)
		return (0);
	env = envp_to_list(envp);
	if (env == NULL)
		return (1);
	minishell(env);
	free_all_env(env);
	rl_clear_history();
	return (0);
}

static void	minishell(t_env *env)
{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
	{
		perror(NULL);
		free_all_env(env);
		rl_clear_history();
		exit(EXIT_FAILURE);
	}
	minishell_loop(env);
}

static void	minishell_loop(t_env *env)
{
	char	*line;

	while (1)
	{
		line = get_input_line();
		if (!line)
		{
			if (!isatty(STDIN_FILENO))
				break ;
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (ft_strlen(line) != 0)
		{
			add_history(line);
			if (parser(line, env))
				continue ;
			exec_cmd(&env, line);
			free(line);
		}
	}
}

static char	*get_input_line(void)
{
	int		stdout_copy;
	int		dev_null;
	char	*line;

	if (isatty(STDIN_FILENO))
		line = readline("\033[1;36mminishell> \033[0m");
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
