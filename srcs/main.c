/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:59:19 by takitaga          #+#    #+#             */
/*   Updated: 2025/02/25 17:57:41 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/* いい感じにまとめる */
char	**get_env_path(char **envp);
char	*get_env_pwd(char **envp);
char	*create_cmd_path(char **envp, char *cmd);
char	**create_cmd_args(char *cmd, char *cmd_path);
void	exec_cmd(char **envp, char *str);

// commandの構造体にする？

// test
int	main(int argc, char **argv, char **envp)
{
	printf("Hello, world!!\n");

	/*
		１：まずはシンプルにls
		２：lsのフルパスで実行する

		３：pwdに実行ファイルをおいて実行してみる
	*/
	// コマンド実行する関数を呼び出す
	exec_cmd(envp, "ls");
	// exec_cmd(envp, "top");
	// exec_cmd(envp, "./test.out");
	// exec_cmd(envp, "/usr/bin/ls");

	// これは怪しい、ヌルが来ない前提で組むべきかも
	// exec_cmd(envp, NULL);

	// catを待つ
	// ビルトインコマンドも実行できる？

	return (0);
}

// allow command and command args
// ex)
// exec_cmd(envp, "ls -l"); -> OK
// exec_cmd(envp, "ls -l home/yohatana/work/minishell"); -> OK
// exec_cmd(envp, "echo "echos args string""); -> OK
// exec_cmd(envp, "ls -l > outfile"); -> NG
void	exec_cmd(char **envp, char *cmd)
{
	char	*cmd_path;
	char	**cmd_args;

	// コマンドパスを作る
	// コマンドの引数を作る
	// 実行する

	cmd_path = create_cmd_path(envp, cmd);
	if (!cmd_path)
		return ;
	printf("cmd_path %s\n", cmd_path);
	cmd_args = create_cmd_args(cmd, cmd_path);
	if (!cmd_args)
		return ;
	// コマンドパスがあろうがなかろうが実行するべき　だった気がする……
	execve(cmd_path, cmd_args, envp);
}

char	*create_cmd_path(char **envp, char *cmd)
{
	char	*cmd_path;
	char	**env_path;
	char	*dir_path;
	int		i;
	char	*cmd_only;

	dir_path = NULL;
	if (cmd[0] == '/')
		return (cmd);
	if (cmd[i] == '.')
	{
		dir_path = get_env_pwd(envp);
		if (!dir_path)
			return (NULL);
	}
	else
	{
		env_path = get_env_path(envp);
		if (!env_path)
			return (NULL);
	}
	i = 0;
	char *temp;
	// cmd not found うーん
	while (env_path[i])
	{
		// 存在したらディレクトリ
		temp = ft_strjoin(env_path[i], cmd_only);
		if (!temp)
			return (NULL);
		if (access(temp, X_OK) == 0)
		{
			cmd_path = temp;
			break ;
		}
		i++;
	}
	cmd_path = ft_strjoin(dir_path, cmd_only);
	return (cmd_path);
}

char	**create_cmd_args(char *cmd, char *cmd_path)
{
	char	**cmd_args;
	int		i;
	int		space_flg;

	i = 0;
	space_flg = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ')
		space_flg = 1;
		i++;
	}
	if (space_flg)
	{
		cmd_args = ft_split(cmd, ' ');
		if (!cmd_args)
			return (NULL);
	}
	return (cmd_args);
}
