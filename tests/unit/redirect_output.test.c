#include "../../includes/minishell.h"

int	main()
{
	t_proc *process;
	t_redirection *redir;
	t_env *env;

	process = ft_calloc(1, sizeof(t_proc));
	process->cmd = "echo -n hello";
	redir = ft_calloc(1, sizeof(t_redirection));
	redir->type = OUTPUT;
	redir->filename = "output.txt";
	env = ft_calloc(1, sizeof(t_env));
	env->key = ft_strdup("HOME");
	env->value = ft_strdup("/home/user");
	redirect(process, redir, env);

	int fd = open("output.txt", O_RDONLY);
	char buffer[100];
	assert(fd != -1);
	int bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	buffer[bytes_read] = '\0';
	close(fd);
	// ファイルに書き込まれた文字列がhelloであることを確認
	assert(strcmp(buffer, "hello") == 0);
	unlink("output.txt");
	return (0);
}
