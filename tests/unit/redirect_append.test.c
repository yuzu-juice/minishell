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
	redir1 = ft_calloc(1, sizeof(t_redirection));
	redir1->type = APPEND;
	redir1->filename = "append1.txt";
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
		exec_cmd(m_shell, process, NULL);
		perror("exec_cmd failed");
		exit(127);
	} else {
		close(pipe_fd[1]);
		int status;
		waitpid(pid, &status, 0);
	}

	int fd = open("append1.txt", O_RDONLY);
	char buffer[100];
	assert(fd != -1);
	int bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	buffer[bytes_read] = '\0';
	close(fd);
	assert(strcmp(buffer, "hello") == 0);

	process->cmd = "echo -n world";
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
		exec_cmd(m_shell, process, NULL);
		perror("exec_cmd failed");
		exit(127);
	} else {
		close(pipe_fd[1]);
		int status;
		waitpid(pid, &status, 0);
	}

	fd = open("append1.txt", O_RDONLY);
	assert(fd != -1);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	buffer[bytes_read] = '\0';
	close(fd);
	assert(strcmp(buffer, "helloworld") == 0);
	unlink("append1.txt");

	redir2 = ft_calloc(1, sizeof(t_redirection));
	redir2->type = APPEND;
	redir2->filename = "append2.txt";
	redir1->next = redir2;
	process->redir = redir1;
	process->cmd = "echo -n test";

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
		exec_cmd(m_shell, process, NULL);
		perror("exec_cmd failed");
		exit(127);
	} else {
		close(pipe_fd[1]);
		int status;
		waitpid(pid, &status, 0);
	}

	fd = open("append1.txt", O_RDONLY);
	assert(fd != -1);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	buffer[bytes_read] = '\0';
	close(fd);
	assert(strcmp(buffer, "") == 0);
	unlink("append1.txt");

	fd = open("append2.txt", O_RDONLY);
	assert(fd != -1);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	buffer[bytes_read] = '\0';
	close(fd);
	assert(strcmp(buffer, "test") == 0);

	process->cmd = "echo -n 123";
	redir1->next = NULL;
	redir1->filename = "append2.txt";
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
		exec_cmd(m_shell, process, NULL);
		perror("exec_cmd failed");
		exit(127);
	} else {
		close(pipe_fd[1]);
		int status;
		waitpid(pid, &status, 0);
	}

	fd = open("append2.txt", O_RDONLY);
	assert(fd != -1);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	buffer[bytes_read] = '\0';
	close(fd);
	assert(strcmp(buffer, "test123") == 0);
	unlink("append2.txt");

	free(env->key);
	free(env->value);
	free(env);
	free(redir1);
	free(redir2);
	free(process);
	free(m_shell);

	return (0);
}
