/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:45:26 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/19 04:21:28 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_input_redir(t_redirection *redir);
static int	handle_output_redir_trunc(t_redirection *redir);
static int	handle_output_redir_append(t_redirection *redir);
static int	handle_output_redir(t_redirection *redir);

int	setup_redirections(t_proc *proc)
{
	t_redirection	*redir;
	int				status;

	redir = proc->redir;
	status = 0;
	while (redir && status == 0)
	{
		if (redir->type == INPUT || redir->type == HEREDOC)
			status = handle_input_redir(redir);
		else if (redir->type == OUTPUT || redir->type == APPEND)
			status = handle_output_redir(redir);
		redir = redir->next;
	}
	return (status);
}

static int	handle_input_redir(t_redirection *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == HEREDOC)
		fd = open(HEREDOC_FILE, O_RDONLY);
	else
		fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->filename);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("minishell: dup2 stdin failed");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	handle_output_redir_trunc(t_redirection *redir)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(redir->filename, flags, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->filename);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("minishell: dup2 stdout failed");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	handle_output_redir_append(t_redirection *redir)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(redir->filename, flags, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->filename);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("minishell: dup2 stdout append failed");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	handle_output_redir(t_redirection *redir)
{
	if (redir->type == OUTPUT)
		return (handle_output_redir_trunc(redir));
	else
		return (handle_output_redir_append(redir));
}
