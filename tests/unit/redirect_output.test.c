#include "../../includes/minishell.h"

int	main()
{
	t_proc *process;
	t_redirection *redir1;
	t_redirection *redir2;
	t_env *env;

	process = ft_calloc(1, sizeof(t_proc));
	process->cmd = "echo -n hello";
	redir1 = ft_calloc(1, sizeof(t_redirection));
	redir1->type = OUTPUT;
	redir1->filename = "output1.txt";
	env = ft_calloc(1, sizeof(t_env));
	env->key = ft_strdup("HOME");
	env->value = ft_strdup("/home/user");
	redirect(process, redir1, env);

	int fd = open("output1.txt", O_RDONLY);
	char buffer[100];
	assert(fd != -1);
	int bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	buffer[bytes_read] = '\0';
	close(fd);
	// ファイルに書き込まれた文字列がhelloであることを確認
	assert(strcmp(buffer, "hello") == 0);
	unlink("output1.txt");

	// リダイレクトを2つ設定
	redir2 = ft_calloc(1, sizeof(t_redirection));
	redir2->type = OUTPUT;
	redir2->filename = "output2.txt";
	redir1->next = redir2;
	redirect(process, redir1, env);
	fd = open("output1.txt", O_RDONLY);
	assert(fd != -1);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	buffer[bytes_read] = '\0';
	close(fd);
	// 一つ目のファイルには何も書き込まれていないことを確認
	assert(strcmp(buffer, "") == 0);
	unlink("output1.txt");
	fd = open("output2.txt", O_RDONLY);
	assert(fd != -1);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	buffer[bytes_read] = '\0';
	close(fd);
	// 二つ目のファイルに書き込まれた文字列がhelloであることを確認
	assert(strcmp(buffer, "hello") == 0);
	unlink("output2.txt");
	return (0);
}
