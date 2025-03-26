#include"../../includes/minishell.h"

int main(void)
{
	t_token		*test;
	t_proc_list	*list;
	int			i;

	char *expect1[] = {"a b"};
	test = create_token_list("a b");
	list = create_process_list(&test);
	t_proc_list *head = list;
	i = 0;
	while (list)
	{
		assert(ft_strcmp(list->proc->cmd, expect1[i]) == 0);
		list = list->next;
		i++;
	}
	free_token_list(&test);
	free_proc_list(&head);

	char *expect2[] = {"a", "b"};
	t_token *test2 = create_token_list("a | b");
	t_proc_list *list2 = create_process_list(&test);
	head = list2;
	i = 0;
	while (list2)
	{
		assert(ft_strcmp(list2->proc->cmd, expect2[i]) == 0);
		list2 = list2->next;
		i++;
	}
	free_token_list(&test2);
	free_proc_list(&head);
	return (0);
}
