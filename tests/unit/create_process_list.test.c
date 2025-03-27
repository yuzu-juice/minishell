#include"../../includes/minishell.h"

int main(void)
{
	t_token		*test;
	t_proc_list	*list;
	int			i;

	char expect1[][100] = {{"a b"}};
	test = create_token_list("a b");
	list = create_process_list(&test);
	t_proc_list *head = list;
	i = 0;
	while (list != NULL)
	{
		assert(ft_strcmp(list->proc->cmd, expect1[i]) == 0);
		list = list->next;
		i++;
	}

	char expect2[][100] = {{"a"}, {"b"}};
	t_token *test2 = create_token_list("a | b");
	t_proc_list *list2 = create_process_list(&test2);
	head = list2;
	i = 0;
	while (list2)
	{
		assert(ft_strcmp(list2->proc->cmd, expect2[i]) == 0);
		list2 = list2->next;
		i++;
	}

	char expect3[][100] = {{"a"}, {"b"}, {"c d"}};
	t_token *test3 = create_token_list("a|b|c d");
	t_proc_list *list3 = create_process_list(&test3);
	head = list3;
	i = 0;
	while (list3)
	{
		assert(ft_strcmp(list3->proc->cmd, expect3[i]) == 0);
		list3 = list3->next;
		i++;
	}

	char expect4[][100] = {{"a\"|\"b"}, {"c"}};
	t_token *test4 = create_token_list("a\"|\"b| c");
	t_proc_list *list4 = create_process_list(&test4);
	head = list4;
	i = 0;
	while (list4)
	{
		assert(ft_strcmp(list4->proc->cmd, expect4[i]) == 0);
		list4 = list4->next;
		i++;
	}

	return (0);
}
