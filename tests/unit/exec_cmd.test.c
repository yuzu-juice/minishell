#include "../../includes/minishell.h"

/*
	allow command and command args
	ex)
	exec_cmd(envp, "ls -l"); -> OK
	exec_cmd(envp, "./a.out"); -> OK
	exec_cmd(envp, "/usr/bin/ls"); -> OK
	exec_cmd(envp, "ls -l home/yohatana/work/minishell"); -> OK
	exec_cmd(envp, "echo "echos args string""); -> OK
	exec_cmd(envp, "ls -l > outfile"); -> NG
*/
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	// コマンド実行する関数を呼び出す
	// exec_cmd(envp, "/usr/bin/ls");
	// exec_cmd(envp, "./test.out");
	// exec_cmd(envp, "ls -l");
	// exec_cmd(envp, "ls");
	// exec_cmd(envp, "top");
	// exec_cmd(envp, "echo aaa sss ddd");

	// 展開不要でした
	// execve("./test.out", NULL, NULL);


	// ビルトインコマンドも実行できる？

	return (0);
}

// cc -Wall -Wextra -Werror test/exec_cmd.c srcs/exec_cmd.c srcs/create_cmd_path.c srcs/get_env_path.c srcs/get_env_pwd.c libft/*.c
