/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:16:44 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/08 16:11:04 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argv;
	if (argc != 1)
		return (0);
	line = NULL;
	while (1)
	{
		line = readline("minishell> ");
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
