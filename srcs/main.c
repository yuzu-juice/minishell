/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:16:44 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/11 14:28:02 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_sig_flag;

static void			minishell(t_env *env);
static void			minishell_loop(t_env *env);
static void			exit_null_line(t_minishell *m_shell);

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
			exit_null_line(m_shell);
		if (ft_strlen(line) != 0)
		{
			add_history(line);
			if (parser(line, m_shell))
			{
				free(line);
				free_proc_list(&(m_shell->proc));
				continue ;
			}
			minishell_pipe(m_shell);
			free(line);
		}
		free_proc_list(&(m_shell->proc));
		m_shell->proc_count = 0;
	}
	free_minishell_struct(m_shell);
}

static void	exit_null_line(t_minishell *m_shell)
{
	free_minishell_struct(m_shell);
	if (!isatty(STDIN_FILENO))
		exit(EXIT_SUCCESS);
	ft_putendl_fd("exit", 1);
	exit(EXIT_SUCCESS);
}
