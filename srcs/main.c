/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:16:44 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/25 18:35:04 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void			minishell(t_env *env);
static void			minishell_loop(t_minishell *m_shell);
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
	t_minishell	*m_shell;

	set_handle_sigint(env);
	m_shell = create_minishell_struct(env);
	if (!m_shell)
		return ;
	minishell_loop(m_shell);
}

static void	minishell_loop(t_minishell *m_shell)
{
	char		*line;

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
				m_shell->prev_status = 1;
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
