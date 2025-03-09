/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:16:44 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/09 14:04:34 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_input_line(char *line);

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argv;
	if (argc != 1)
		return (0);
	line = NULL;
	while (1)
	{
		line = get_input_line(line);
		if (ft_strlen(line) != 0)
		{
			add_history(line);
			parser(argc, argv, line);
			exec_cmd(envp, line);
			free(line);
		}
	}
	return (0);
}

static char	*get_input_line(char *line)
{
	int	stdout_copy;
	int	dev_null;

	if (isatty(STDIN_FILENO))
		line = readline("minishell> ");
	else
	{
		stdout_copy = dup(STDOUT_FILENO);
		if (stdout_copy == -1)
			return (NULL);
		dev_null = open("/dev/null", O_WRONLY);
		if (dev_null == -1)
			return (NULL);
		dup2(dev_null, STDOUT_FILENO);
		close(dev_null);
		line = readline("");
		dup2(stdout_copy, STDOUT_FILENO);
		close(stdout_copy);
	}
	return (line);
}
