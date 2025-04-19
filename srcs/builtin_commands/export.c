/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:42:27 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/19 19:05:53 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	print_env(t_minishell *m_shell);

int	export(int argc, char **argv, t_minishell *m_shell)
{
	int		i;
	bool	err_flg;
	int		err_count;

	err_flg = false;
	err_count = 0;
	if (argc == 1)
		return (print_env(m_shell));
	else if (argc > 1)
	{
		i = 1;
		while (argv[i])
		{
			if (add_env_node(m_shell->env, argv[i], 1))
				err_count++;
			i++;
		}
		if (err_count)
		{
			perror(NULL);
			return (1);
		}
		return (0);
	}
	return (0);
}

static int	print_env(t_minishell *m_shell)
{
	t_env	*tmp;

	tmp = m_shell->env;
	while (tmp)
	{
		if (tmp->value == NULL)
		{
			write(1, tmp->key, ft_strlen(tmp->key));
			write(1, "\n", 1);
		}
		else
		{
			write(1, tmp->key, ft_strlen(tmp->key));
			write(1, "=", 1);
			write(1, tmp->value, ft_strlen(tmp->value));
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
