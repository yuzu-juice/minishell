/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:41:51 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/26 12:08:27 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

typedef enum e_redirection_type
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
}	t_redirection_type;

typedef struct s_redirection	t_redirection;

typedef struct s_redirection
{
	char				*filename;
	t_redirection_type	type;
	t_redirection		*next;
}	t_redirection;

void	redirect(t_proc *process, t_redirection *redir, t_env *env);

#endif
