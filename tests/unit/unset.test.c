#include "../../includes/minishell.h"
#include <assert.h>

int main(void)
{
    char *test_envp[] = {
        "HOME=/home/user",
        "PATH=/usr/bin:/bin",
        "USER=tester",
        "PWD=/workspaces",
        NULL
    };

    t_env *env_list = envp_to_list(test_envp);
    t_env *original_list = env_list;
	t_minishell *m_shell;
	m_shell = ft_calloc(sizeof(t_minishell), 1);
	m_shell->env = env_list;

    t_env *tmp = m_shell->env;

    // 中間ノードのunsetテスト
    char *unset_args[] = {"unset", "PATH"};
    unset(2, unset_args, m_shell);

    tmp = m_shell->env;
    while (tmp)
    {
        assert(strcmp(tmp->key, "PATH") != 0);  // PATHが存在しないことを確認
        tmp = tmp->next;
    }

    // 環境変数リストを再作成
    m_shell->env = envp_to_list(test_envp);

    // 先頭ノードのunsetテスト
    char *unset_home[] = {"unset", "HOME"};
    unset(2, unset_home, m_shell);

    tmp = m_shell->env;
    while (tmp)
    {
        assert(strcmp(tmp->key, "HOME") != 0);
        tmp = tmp->next;
    }

    // 先頭がPATHになっていることを確認
    assert(strcmp(m_shell->env->key, "PATH") == 0);

    // 最後のノードのunsetテスト
    char *unset_pwd[] = {"unset", "PWD"};
    unset(2, unset_pwd, m_shell);

    tmp = m_shell->env;
    while (tmp)
    {
        assert(strcmp(tmp->key, "PWD") != 0);
        tmp = tmp->next;
    }

    return (0);
}
