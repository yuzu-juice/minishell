/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:45:26 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/30 15:51:19 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	output(char *cmd, t_redirection *redir, t_env *env);
static void input(char *cmd, t_redirection *redir, t_env *env);
static void here_doc(char *cmd, t_redirection *redir, t_env *env);
static void	input(char *cmd, t_redirection *redir, t_env *env);

void	redirect(char *cmd, t_redirection *redir, t_env *env)
{
	while (redir)
	{
		if (redir->type == OUTPUT)
			output(cmd, redir, env);
		else if (redir->type == INPUT)
			input(cmd, redir, env);
		else if (redir->type == HEREDOC)
			here_doc(cmd, redir, env);
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

static void	input(char *cmd, t_redirection *redir, t_env *env)
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
		exec_cmd(&env, cmd);
	close(infile_fd);
}

static void	here_doc(char *cmd, t_redirection *redir, t_env *env)
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
	input(cmd, redir, env);
}
