/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:08:44 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/19 13:24:33 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*generate_heredoc_filename(void);
static int	write_to_heredoc(int fd, const char *delimiter);

int	handle_input_redir(t_redirection *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->filename);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_heredoc_redir(t_redirection *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell: open heredoc temp file");
		return (1);
	}
	unlink(redir->filename);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("minishell: dup2 heredoc");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	create_heredoc_file(t_redirection *redir)
{
	int		fd;
	char	*temp_filename;
	char	*delimiter;

	temp_filename = generate_heredoc_filename();
	if (!temp_filename)
		return (1);
	fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("minishell: create heredoc temp file");
		return (free(temp_filename), 1);
	}
	delimiter = redir->filename;
	if (write_to_heredoc(fd, delimiter) != 0)
	{
		close(fd);
		unlink(temp_filename);
		free(temp_filename);
		return (1);
	}
	close(fd);
	free(redir->filename);
	redir->filename = temp_filename;
	return (0);
}

static char	*generate_heredoc_filename(void)
{
	static int	heredoc_index = 0;
	char		*index_str;
	char		*filename;
	char		*base;

	base = "/tmp/minishell_heredoc_";
	index_str = ft_itoa(heredoc_index++);
	if (!index_str)
	{
		perror("minishell: ft_itoa");
		return (NULL);
	}
	filename = ft_strjoin(base, index_str);
	free(index_str);
	if (!filename)
	{
		perror("minishell: ft_strjoin");
		return (NULL);
	}
	return (filename);
}

static int	write_to_heredoc(int fd, const char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, (char *)delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (0);
}
