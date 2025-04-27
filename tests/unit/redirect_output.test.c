#include "../../includes/minishell.h"

int	main()
{
	t_proc *process;
	t_redirection *redir1;
	t_redirection *redir2;
	t_env *env;
	t_minishell *m_shell;

	process = ft_calloc(1, sizeof(t_proc));
	process->cmd = "echo -n hello";
	process->cmd_args = ft_calloc(sizeof(char *), 10);
	process->cmd_args[0] = ft_strdup("echo");
	process->cmd_args[1] = ft_strdup("-n");
	process->cmd_args[2] = ft_strdup("hello");
	process->cmd_args[3] = NULL;
	redir1 = ft_calloc(1, sizeof(t_redirection));
	redir1->type = OUTPUT;
	redir1->filename = "output1.txt";
	process->redir = redir1;
	env = ft_calloc(1, sizeof(t_env));
	env->key = ft_strdup("HOME");
	env->value = ft_strdup("/home/user");
	m_shell = ft_calloc(sizeof(t_minishell), 1);
	m_shell->env = env;

	int pipe_fd[2];
	if (pipe(pipe_fd) == -1) {
		perror("pipe failed");
		return 1;
	}

	pid_t pid = fork();
	if (pid == -1) {
		perror("fork failed");
		return 1;
	}

	if (pid == 0) {
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		if (setup_redirections(process) != 0)
			exit(1);
		exec_cmd(m_shell, process);
		perror("exec_cmd failed");
		exit(127);
	} else {
		close(pipe_fd[1]);
		int status;
		waitpid(pid, &status, 0);
	}

	int fd = open("output1.txt", O_RDONLY);
	char buffer[100];
	assert(fd != -1);
	int bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	buffer[bytes_read] = '\0';
	close(fd);
	assert(strcmp(buffer, "hello") == 0);
	unlink("output1.txt");

	redir2 = ft_calloc(1, sizeof(t_redirection));
	redir2->type = OUTPUT;
	redir2->filename = "output2.txt";
	redir1->next = redir2;
	process->redir = redir1;

	if (pipe(pipe_fd) == -1) {
		perror("pipe failed");
		return 1;
	}

	pid = fork();
	if (pid == -1) {
		perror("fork failed");
		return 1;
	}

	if (pid == 0) {
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		if (setup_redirections(process) != 0)
			exit(1);
		exec_cmd(m_shell, process);
		perror("exec_cmd failed");
		exit(127);
	} else {
		close(pipe_fd[1]);
		int status;
		waitpid(pid, &status, 0);
	}

	fd = open("output1.txt", O_RDONLY);
	assert(fd != -1);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	buffer[bytes_read] = '\0';
	close(fd);
	assert(strcmp(buffer, "") == 0);
	unlink("output1.txt");
	fd = open("output2.txt", O_RDONLY);
	assert(fd != -1);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	buffer[bytes_read] = '\0';
	close(fd);
	assert(strcmp(buffer, "hello") == 0);
	unlink("output2.txt");

	fd = open("existing.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	assert(fd != -1);
	write(fd, "previous content", 16);
	close(fd);

	redir1->filename = "existing.txt";
	redir1->next = NULL;
	process->redir = redir1;
	process->cmd = "echo -n overwritten";
	process->cmd_args[0] = ft_strdup("echo");
	process->cmd_args[1] = ft_strdup("-n");
	process->cmd_args[2] = ft_strdup("overwritten");
	process->cmd_args[3] = NULL;

	if (pipe(pipe_fd) == -1) {
		perror("pipe failed");
		return 1;
	}

	pid = fork();
	if (pid == -1) {
		perror("fork failed");
		return 1;
	}

	if (pid == 0) {
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		if (setup_redirections(process) != 0)
			exit(1);
		exec_cmd(m_shell, process);
		perror("exec_cmd failed");
		exit(127);
	} else {
		close(pipe_fd[1]);
		int status;
		waitpid(pid, &status, 0);
	}

	fd = open("existing.txt", O_RDONLY);
	assert(fd != -1);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	buffer[bytes_read] = '\0';
	close(fd);
	assert(strcmp(buffer, "overwritten") == 0);
	unlink("existing.txt");

	free(env->key);
	free(env->value);
	free(env);
	free(redir1);
	free(redir2);
	free(process);
	free(m_shell);

	return (0);
}

