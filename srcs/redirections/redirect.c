/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:45:26 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/06 14:43:24 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	output(char *cmd, t_redirection *redir, t_minishell *m_shell);
static void	append(char *cmd, t_redirection *redir, t_minishell *m_shell);
static void	input(char *cmd, t_redirection *redir, t_minishell *m_shell);
static void	here_doc(char *cmd, t_redirection *redir, t_minishell *m_shell);
static void	input(char *cmd, t_redirection *redir, t_minishell *m_shell);

void	redirect(char *cmd, t_redirection *redir, t_minishell *m_shell)
{
	while (redir)
	{
		if (redir->type == OUTPUT)
			output(cmd, redir, m_shell);
		else if (redir->type == INPUT)
			input(cmd, redir, m_shell);
		else if (redir->type == HEREDOC)
			here_doc(cmd, redir, m_shell);
		if (redir->type == APPEND)
			append(cmd, redir, m_shell);
		redir = redir->next;
	}
}

static void	output(char *cmd, t_redirection *redir, t_minishell *m_shell)
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
		exec_cmd(m_shell, cmd);
	close(outfile_fd);
}

static void	input(char *cmd, t_redirection *redir, t_minishell *m_shell)
{
	int	infile_fd;

	infile_fd = open(redir->filename, O_RDONLY, 0644);
	if (infile_fd < 0)
	{
		perror("open");
		return ;
	}
	dup2(infile_fd, STDIN_FILENO);
	if (redir->next == NULL)
		exec_cmd(m_shell, cmd);
	close(infile_fd);
}

static void	here_doc(char *cmd, t_redirection *redir, t_minishell *m_shell)
{
	int		heredoc_file_fd;
	char	*line;

	heredoc_file_fd = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_file_fd < 0)
	{
		perror("open");
		return ;
	}
	while (true)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, redir->filename) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, heredoc_file_fd);
		free(line);
	}
	close(heredoc_file_fd);
	redir->filename = HEREDOC_FILE;
	input(cmd, redir, m_shell);
}

static void	append(char *cmd, t_redirection *redir, t_minishell *m_shell)
{
	int	outfile_fd;

	outfile_fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile_fd < 0)
	{
		perror("open");
		return ;
	}
	dup2(outfile_fd, STDOUT_FILENO);
	if (redir->next == NULL)
		exec_cmd(m_shell, cmd);
	close(outfile_fd);
}
