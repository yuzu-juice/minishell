/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:51:45 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/23 12:11:52 by takitaga         ###   ########.fr       */
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
void	unset(int argc, char **argv, t_env *env);

#endif
