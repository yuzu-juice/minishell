/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:41:51 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/26 14:11:11 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

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

int		setup_redirections(t_proc *proc);
int		handle_input_redir(t_redirection *redir);
int		handle_heredoc_redir(t_redirection *redir);
int		handle_output_redir(t_redirection *redir);
int		handle_append_redir(t_redirection *redir);
int		create_heredoc_file(t_redirection *redir);
void	free_redirection_list(t_redirection **list);

#endif
