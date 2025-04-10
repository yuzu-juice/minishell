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
        redirect(process->cmd, redir1, m_shell);
        exit(0);
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
    // 基本的な追記リダイレクトのテスト
    assert(strcmp(buffer, "hello") == 0);

    // 既存のファイルに追記するテスト
    process->cmd = "echo -n world";

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
        redirect(process->cmd, redir1, m_shell);
        exit(0);
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
    // 追記した結果、"helloworld"になっていることを確認
    assert(strcmp(buffer, "helloworld") == 0);
    unlink("append1.txt");

    // 複数のリダイレクトを設定
    redir2 = ft_calloc(1, sizeof(t_redirection));
    redir2->type = APPEND;
    redir2->filename = "append2.txt";
    redir1->next = redir2;
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
        redirect(process->cmd, redir1, m_shell);
        exit(0);
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
    // 一つ目のファイルには何も書き込まれていないことを確認
    assert(strcmp(buffer, "") == 0);
    unlink("append1.txt");

    fd = open("append2.txt", O_RDONLY);
    assert(fd != -1);
    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    buffer[bytes_read] = '\0';
    close(fd);
    // 二つ目のファイルに書き込まれた文字列がtestであることを確認
    assert(strcmp(buffer, "test") == 0);

    // 同じファイルに複数回追記
    process->cmd = "echo -n 123";
    redir1->next = NULL; // 一つのリダイレクトに戻す
    redir1->filename = "append2.txt"; // 既存のファイルを使用

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
        redirect(process->cmd, redir1, m_shell);
        exit(0);
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
    // 既存の内容に追記されていることを確認
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
