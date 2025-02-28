/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:16:44 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/28 16:36:29 by yohatana         ###   ########.fr       */
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
			// レキサー
			// パイプする
			// 子プロセス作る
				// リダイレクトの処理
			exec_cmd(envp, line);
			free(line);
		}
	}
	return (0);
}

