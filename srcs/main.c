/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:16:44 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/28 16:11:18 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	ほんものmain
*/
// int	main(void)
// {
// 	char	*line;

// 	line = NULL;
// 	while (1)
// 	{
// 		line = readline("minishell> ");
// 		if (line == NULL || strlen(line) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		// 実処理
// 		printf("%s\n", line);

// 		free(line);
// 	}
// 	return (0);
// }

// test
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	// ok
	exec_cmd(envp, "/usr/bin/ls");
	// exec_cmd(envp, "./test.out");
	// exec_cmd(envp, "ls -l");
	// exec_cmd(envp, "ls");
	// exec_cmd(envp, "top");

	// NG
	// 存在しないコマンド->No such file or directoryになる
	// exec_cmd(envp, "ca");

	// builtinはこの機能では対応不要
	// exec_cmd(envp, "cd");
	return (0);
}
