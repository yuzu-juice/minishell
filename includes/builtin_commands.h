/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:51:45 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/19 19:09:01 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_COMMANDS_H
# define BUILTIN_COMMANDS_H

# include <unistd.h>

typedef enum e_builtin
{
	NOT_A_BUILTIN_COMMAND,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
}	t_builtin;

int	echo(int argc, char **argv);
int	pwd(int argc);
int	cd(int argc, char **argv);
int	unset(int argc, char **argv, t_minishell *m_shell);
int	env(int argc, t_minishell *m_shell);
int	export(int argc, char **argv, t_minishell *m_shell);
int	minishell_exit(int argc, char **argv, t_minishell *m_shell);

#endif
