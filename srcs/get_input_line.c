/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:25:24 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/06 14:25:56 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_input_line(void)
{
	int		stdout_copy;
	int		dev_null;
	char	*line;

	if (isatty(STDIN_FILENO))
		line = readline("\033[1;36mminishell> \033[0m");
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
