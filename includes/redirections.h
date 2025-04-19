/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:41:51 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/19 04:19:15 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H
# define HEREDOC_FILE "/tmp/heredoc"

typedef struct s_proc			t_proc;
typedef struct s_redirection	t_redirection;
typedef struct s_minishell		t_minishell;

typedef enum e_redirection_type
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
}	t_redirection_type;

typedef struct s_redirection
{
	char				*filename;
	t_redirection_type	type;
	t_redirection		*next;
}	t_redirection;

int	setup_redirections(t_proc *proc);

#endif
