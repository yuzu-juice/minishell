/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:45:26 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/27 03:13:57 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	output(char *cmd, t_redirection *redir, t_env *env);

void	redirect(char *cmd, t_redirection *redir, t_env *env)
{
	while (redir)
	{
		if (redir->type == OUTPUT)
			output(cmd, redir, env);
		redir = redir->next;
	}
}

static void	output(char *cmd, t_redirection *redir, t_env *env)
{
	int	outfile_fd;

	outfile_fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		perror("open");
		return ;
	}
	dup2(outfile_fd, STDOUT_FILENO);
	if (redir->next == NULL)
		exec_cmd(&env, cmd);
	close(outfile_fd);
}
