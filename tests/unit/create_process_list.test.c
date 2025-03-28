#include"../../includes/minishell.h"

int	main(void)
{
	t_token	*test;
	t_proc	*list;
	int			i;

	char expect1[][100] = {{"a b"}};
	test = create_token_list("a b");
	list = create_process_list(&test);
	t_proc *head = list;
	i = 0;
	while (list != NULL)
	{
		assert(ft_strcmp(list->cmd, expect1[i]) == 0);
		list = list->next;
		i++;
	}

	char expect2[][100] = {{"a"}, {"b"}};
	t_token *test2 = create_token_list("a | b");
	t_proc *list2 = create_process_list(&test2);
	head = list2;
	i = 0;
	while (list2)
	{
		assert(ft_strcmp(list2->cmd, expect2[i]) == 0);
		list2 = list2->next;
		i++;
	}

	char expect3[][100] = {{"a"}, {"b"}, {"c d"}};
	t_token *test3 = create_token_list("a|b|c d");
	t_proc *list3 = create_process_list(&test3);
	head = list3;
	i = 0;
	while (list3)
	{
		assert(ft_strcmp(list3->cmd, expect3[i]) == 0);
		list3 = list3->next;
		i++;
	}

	char expect4[][100] = {{"a\"|\"b"}, {"c"}};
	t_token *test4 = create_token_list("a\"|\"b| c");
	t_proc *list4 = create_process_list(&test4);
	head = list4;
	i = 0;
	while (list4)
	{
		assert(ft_strcmp(list4->cmd, expect4[i]) == 0);
		list4 = list4->next;
		i++;
	}

	t_token *test5 = create_token_list("a || b");
	t_proc *list5 = create_process_list(&test5);
	head = list5;
	i = 0;
	while (list5)
	{
		assert(list5 ==  NULL);
		list5 = list5->next;
		i++;
	}

	return (0);
}
