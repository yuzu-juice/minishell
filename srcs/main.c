/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:16:44 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/06 14:36:12 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_sig_flag;

static void			minishell(t_env *env);
static void			minishell_loop(t_env *env);
static void			exit_null_line(void);

int	main(int argc, char **argv, char **envp)
{
	t_env		*env;

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
	char		*line;
	t_minishell	*m_shell;

	m_shell = create_minishell_struct(env);
	if (!m_shell)
		return ;
	while (1)
	{
		line = get_input_line();
		if (!line)
			exit_null_line();
		if (ft_strlen(line) != 0)
		{
			add_history(line);
			if (parser(line, m_shell))
				continue ;
			free(line);
		}
		free_proc_list(&m_shell->proc);
	}
	free_minishell_struct(m_shell);
}

static void	exit_null_line(void)
{
	if (!isatty(STDIN_FILENO))
		exit(EXIT_SUCCESS);
	ft_putendl_fd("exit", 1);
	exit(EXIT_SUCCESS);
}
