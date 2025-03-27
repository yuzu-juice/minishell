#include "../../includes/minishell.h"
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// heredoc入力をシミュレート
void simulate_heredoc_input(int write_fd, const char* content, const char* delimiter) {
    write(write_fd, content, strlen(content));
    write(write_fd, delimiter, strlen(delimiter));
    write(write_fd, "\n", 1);
}

// プロンプトの行を取り除き、実際の出力内容のみを抽出する
char* strip_prompt_lines(const char* output) {
    char* result = strdup(output);
    char* dest = result;
    char* src = result;
    
    while (*src) {
        // '>' で始まる行をスキップ
        if (*src == '>') {
            while (*src && *src != '\n') {
                src++;
            }
            if (*src) src++; // 改行もスキップ
            continue;
        }
        
        *dest++ = *src++;
    }
    *dest = '\0';
    
    return result;
}

int main() {
    // テスト1: 単一のheredocリダイレクション
    t_proc *process = ft_calloc(1, sizeof(t_proc));
    t_redirection *redir = ft_calloc(1, sizeof(t_redirection));
    t_env *env = ft_calloc(1, sizeof(t_env));
    
    process->cmd = "cat";
    redir->type = HEREDOC;
    redir->filename = ft_strdup("EOF");
    redir->next = NULL;
    env->key = ft_strdup("HOME");
    env->value = ft_strdup("/home/user");
    
    // heredoc入力用のパイプ
    int in_pipe[2];
    if (pipe(in_pipe) == -1) {
        perror("pipe failed");
        return 1;
    }
    
    // 出力キャプチャ用のパイプ
    int out_pipe[2];
    if (pipe(out_pipe) == -1) {
        perror("pipe failed");
        return 1;
    }
    
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        return 1;
    }
    
    if (pid == 0) {
        close(in_pipe[1]);
        close(out_pipe[0]);
        
        dup2(in_pipe[0], STDIN_FILENO);
        dup2(out_pipe[1], STDOUT_FILENO);
        
        close(in_pipe[0]);
        close(out_pipe[1]);
        
        redirect(process->cmd, redir, env);
        exit(0);
    } else {
        close(in_pipe[0]);
        close(out_pipe[1]);
        
        const char *content = "This is a heredoc test\nWith multiple lines\n";
        simulate_heredoc_input(in_pipe[1], content, "EOF");
        close(in_pipe[1]);
        
        int status;
        waitpid(pid, &status, 0);
        
        char buffer[1024] = {0};
        int bytes_read = read(out_pipe[0], buffer, sizeof(buffer) - 1);
        close(out_pipe[0]);
        
        buffer[bytes_read] = '\0';
        
        // プロンプト行を取り除いた出力を取得
        char* cleaned_output = strip_prompt_lines(buffer);
        assert(strcmp(cleaned_output, content) == 0);
        free(cleaned_output);
    }
    
    free(redir->filename);
    free(redir);
    free(env->key);
    free(env->value);
    free(env);
    free(process);
    unlink(HEREDOC_FILE);
    
    return 0;
}
