#include "../../includes/minishell.h"

int main() {
    t_proc *process;
    t_redirection *redir1;
    t_env *env;

    process = ft_calloc(1, sizeof(t_proc));
    process->cmd = "cat";
    redir1 = ft_calloc(1, sizeof(t_redirection));
    redir1->type = INPUT;
    redir1->filename = "input.txt";
    env = ft_calloc(1, sizeof(t_env));
    env->key = ft_strdup("HOME");
    env->value = ft_strdup("/home/user");

    // input.txt に "hoge" を書き込む
    int fd = open(redir1->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    write(fd, "hoge", 4);
    close(fd);

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    int pid = fork();
    if (pid == 0)
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);

        redirect(process->cmd, redir1, env);
    }
    else
    {
        close(pipe_fd[1]);

        int status;
        waitpid(pid, &status, 0);

        char buffer[100];
        int bytes_read = read(pipe_fd[0], buffer, sizeof(buffer) - 1);
        buffer[bytes_read] = '\0';
        assert(strcmp(buffer, "hoge") == 0);
        close(pipe_fd[0]);
    }

    unlink("input.txt");
    free(env->key);
    free(env->value);
    free(env);
    free(redir1);
    free(process);

    return (0);
}
