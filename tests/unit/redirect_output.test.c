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
        redirect(process->cmd, redir1, env);
        exit(0);
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
    // ファイルに書き込まれた文字列がhelloであることを確認
    assert(strcmp(buffer, "hello") == 0);
    unlink("output1.txt");

    // リダイレクトを2つ設定
    redir2 = ft_calloc(1, sizeof(t_redirection));
    redir2->type = OUTPUT;
    redir2->filename = "output2.txt";
    redir1->next = redir2;
    
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
        redirect(process->cmd, redir1, env);
        exit(0);
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

    // 既存のファイルに対するリダイレクトのテスト
    fd = open("existing.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    assert(fd != -1);
    write(fd, "previous content", 16);
    close(fd);

    redir1->filename = "existing.txt";
    redir1->next = NULL;
    process->cmd = "echo -n overwritten";
    
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
        redirect(process->cmd, redir1, env);
        exit(0);
    } else {
        close(pipe_fd[1]);
        int status;
        waitpid(pid, &status, 0);
    }

    // ファイルの内容が上書きされていることを確認
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

    return (0);
}
