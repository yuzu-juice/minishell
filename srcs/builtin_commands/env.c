/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:49:16 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/19 18:57:15 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error(void);

/*
yohatana@c6r3s7:~/work/minishell$ env aaaa
env: ‘aaaa’: No such file or directory
yohatana@c6r3s7:~/work/minishell$ echo $?
127

yohatana@c6r3s7:~/work/minishell$ ls
aa	  libft     minishell	    readline.supp  srcs   uv.lock
includes  Makefile  pyproject.toml  README.md	   tests
yohatana@c6r3s7:~/work/minishell$ env libft
env: ‘libft’: No such file or directory
yohatana@c6r3s7:~/work/minishell$ echo $?
127

*/
int	env(int argc, t_minishell *m_shell)
{
	t_env	*tmp;

	if (argc != 1 || m_shell->env == NULL)
	{
		error();
		return (127);
	}
	tmp = m_shell->env;
	while (tmp)
	{
		if (tmp->value != NULL)
		{
			write(1, tmp->key, ft_strlen(tmp->key));
			write(1, "=", 1);
			ft_putendl_fd(tmp->value, 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	error(void)
{
	ft_putendl_fd("Usage: env", 2);
}
