/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:15:38 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/19 20:40:38 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error(void);
// static char	*get_relative_path(char *relative_path, char *argv);

// TODO
/*
	親でも子でも変わらない
	yohatana@c6r3s7:~/work/minishell$ chmod 000 aa
	yohatana@c6r3s7:~/work/minishell$ cd aa
	bash: cd: aa: Permission denied
	yohatana@c6r3s7:~/work/minishell$ echo $?
	1
	yohatana@c6r3s7:~/work/minishell$ cd no
	bash: cd: no: No such file or directory
	yohatana@c6r3s7:~/work/minishell$ echo $?
	1

	cd .. これ対応する
	OLDPWD 前のディレクトリを保管できる（めっちゃ使う）
*/
int	cd(int argc, char **argv)
{
	char	*relative_path;

	relative_path = NULL;
	if (argc != 2)
	{
		error();
		return (1);
	}
	// ..はじまりのときaccess(argv[1], X_OK)が失敗する可能性
	if (access(argv[1], F_OK) == 0)
	{
		if (chdir(argv[1]) == -1)
		{
			perror(argv[1]);
			return (1);
		}
	}
	else
	{
		perror(argv[1]);
		return (1);
	}
	return (0);
}

static void	error(void)
{
	ft_putendl_fd("Usage: cd [relative path | absolute path]", 2);
}
