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

    t_env *tmp = env_list;
    
    // 中間ノードのunsetテスト
    char *unset_args[] = {"unset", "PATH"};
    unset(2, unset_args, &env_list);

    tmp = env_list;
    while (tmp)
    {
        assert(strcmp(tmp->key, "PATH") != 0);  // PATHが存在しないことを確認
        tmp = tmp->next;
    }

    // 環境変数リストを再作成
    env_list = envp_to_list(test_envp);
    
    // 先頭ノードのunsetテスト
    char *unset_home[] = {"unset", "HOME"};
    unset(2, unset_home, &env_list);
    
    tmp = env_list;
    while (tmp)
    {
        assert(strcmp(tmp->key, "HOME") != 0);
        tmp = tmp->next;
    }
    
    // 先頭がPATHになっていることを確認
    assert(strcmp(env_list->key, "PATH") == 0);
    
    // 最後のノードのunsetテスト
    char *unset_pwd[] = {"unset", "PWD"};
    unset(2, unset_pwd, &env_list);
    
    tmp = env_list;
    while (tmp)
    {
        assert(strcmp(tmp->key, "PWD") != 0);
        tmp = tmp->next;
    }
    
    return (0);
}
