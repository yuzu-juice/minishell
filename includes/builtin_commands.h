/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:51:45 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/06 16:09:18 by yohatana         ###   ########.fr       */
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

void	echo(int argc, char **argv);
void	pwd(int argc);
void	cd(int argc, char **argv);
void	unset(int argc, char **argv, t_minishell *m_shell);
void	env(int argc, t_minishell *m_shell);
void	export(int argc, char **argv, t_minishell *m_shell);
void	minishell_exit(int argc, char **argv);

#endif
