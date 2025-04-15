/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_minishell_struct.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:28:21 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/06 16:55:46 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_minishell	*create_minishell_struct(t_env *env)
{
	t_minishell	*m_shell;

	m_shell = (t_minishell *)ft_calloc(sizeof(t_minishell), 1);
	if (!m_shell)
	{
		ft_putendl_fd("failed: malloc\n", 2);
		return (NULL);
	}
	m_shell->env = env;
	m_shell->proc_count = 0;
	return (m_shell);
}

void	free_minishell_struct(t_minishell *m_shell)
{
	free_all_env(m_shell->env);
	free(m_shell);
	m_shell = NULL;
}
