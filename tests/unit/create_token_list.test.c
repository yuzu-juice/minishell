
#include "../../includes/minishell.h"

int	main(void)
{
	t_token *head;
	t_token	*temp;
	int		i;
	char	*expect;

	// normal only token
	head = create_token_list("a");
	char	array1[][100] = {{"a"}};
	temp = head;
	i = 0;
	while (temp)
	{
		expect = array1[i];
		assert(strncmp(temp->word, expect, 1) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("a b");
	temp = head;
	char	array2[][100] = {{"a"}, {"b"}};
	while (temp)
	{
		expect = array2[i];
		assert(strncmp(temp->word, expect, 1) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("ab cde fgh");
	temp = head;
	char	array3[][100] = {{"ab"}, {"cde"}, {"fgh"}};
	while (temp)
	{
		expect = array3[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("a           b");
	temp = head;
	char	array4[][100] = {{"a"}, {"b"}};
	while (temp)
	{
		expect = array4[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	// single quart
	i = 0;
	head = create_token_list("\'a\'");
	temp = head;
	char	array5[][100] = {{"\'a\'"}};
	while (temp)
	{
		expect = array5[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("\'a\' \'b\'");
	temp = head;
	char	array6[][100] = {{"\'a\'"}, {"\'b\'"}};
	while (temp)
	{
		expect = array6[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("\'a\'\'b\'");
	temp = head;
	char	array7[][100] = {{"\'a\'\'b\'"}};
	while (temp)
	{
		expect = array7[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("\'a\'b");
	temp = head;
	char	array8[][100] = {{"\'a\'b"}};
	while (temp)
	{
		expect = array8[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("a\'b\'");
	temp = head;
	char	array9[][100] = {{"a\'b\'"}};
	while (temp)
	{
		expect = array9[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("\'a\' \'b\' c");
	temp = head;
	char	array10[][100] = {{"\'a\'"}, {"\'b\'"}, {"c"}};
	while (temp)
	{
		expect = array10[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("\'|\'");
	temp = head;
	char	split_char1[][100] = {{"\'|\'"}};
	while (temp)
	{
		expect = split_char1[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("\'<\'");
	temp = head;
	char	split_char2[][100] = {{"\'<\'"}};
	while (temp)
	{
		expect = split_char2[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("\'>\'");
	temp = head;
	char	split_char3[][100] = {{"\'>\'"}};
	while (temp)
	{
		expect = split_char3[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("\'<<\'");
	temp = head;
	char	split_char4[][100] = {{"\'<<\'"}};
	while (temp)
	{
		expect = split_char4[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("\'>>\'");
	temp = head;
	char	split_char5[][100] = {{"\'>>\'"}};
	while (temp)
	{
		expect = split_char5[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	// double quart
	i = 0;
	head = create_token_list("\"a\"");
	temp = head;
	char	array11[][100] = {{"\"a\""}};
	while (temp)
	{
		expect = array11[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("\"a\" \"b\"");
	temp = head;
	char	array12[][100] = {{"\"a\""}, {"\"b\""}};
	while (temp)
	{
		expect = array12[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("\"a\"\"b\"");
	temp = head;
	char	array13[][100] = {{"\"a\"\"b\""}};
	while (temp)
	{
		expect = array13[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("\"a\"b");
	temp = head;
	char	array14[][100] = {{"\"a\"b"}};
	while (temp)
	{
		expect = array14[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("a\"b\"");
	temp = head;
	char	array15[][100] = {{"a\"b\""}};
	while (temp)
	{
		expect = array15[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("\"a\" \"b\" c");
	temp = head;
	char	array16[][100] = {{"\"a\""}, {"\"b\""}, {"c"}};
	while (temp)
	{
		expect = array16[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);


	i = 0;
	head = create_token_list("\'|\'");
	temp = head;
	char	split_char6[][100] = {{"\'|\'"}};
	while (temp)
	{
		expect = split_char6[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("\'<\'");
	temp = head;
	char	split_char7[][100] = {{"\'<\'"}};
	while (temp)
	{
		expect = split_char7[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("\'>\'");
	temp = head;
	char	split_char8[][100] = {{"\'>\'"}};
	while (temp)
	{
		expect = split_char8[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("\'<<\'");
	temp = head;
	char	split_char9[][100] = {{"\'<<\'"}};
	while (temp)
	{
		expect = split_char9[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("\'>>\'");
	temp = head;
	char	split_char10[][100] = {{"\'>>\'"}};
	while (temp)
	{
		expect = split_char10[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	// pipe
	i = 0;
	head = create_token_list("|");
	temp = head;
	char	array17[][100] = {{"|"}};
	while (temp)
	{
		expect = array17[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("a | b");
	temp = head;
	char	array18[][100] = {{"a"}, {"|"}, {"b"}};
	while (temp)
	{
		expect = array18[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("a|b");
	temp = head;
	char	array19[][100] = {{"a"}, {"|"}, {"b"}};
	while (temp)
	{
		expect = array19[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	// redirect
	i = 0;
	head = create_token_list("<");
	temp = head;
	char	array20[][100] = {{"<"}};
	while (temp)
	{
		expect = array20[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("a < b");
	temp = head;
	char	array21[][100] = {{"a"}, {"<"}, {"b"}};
	while (temp)
	{
		expect = array21[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("a<b");
	temp = head;
	char	array22[][100] = {{"a"}, {"<"}, {"b"}};
	while (temp)
	{
		expect = array22[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list(">");
	temp = head;
	char	array23[][100] = {{">"}};
	while (temp)
	{
		expect = array23[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("a > b");
	temp = head;
	char	array24[][100] = {{"a"}, {">"}, {"b"}};
	while (temp)
	{
		expect = array24[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("a>b");
	temp = head;
	char	array25[][100] = {{"a"}, {">"}, {"b"}};
	while (temp)
	{
		expect = array25[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("<<");
	temp = head;
	char	array26[][100] = {{"<<"}};
	while (temp)
	{
		expect = array26[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("a << b");
	temp = head;
	char	array27[][100] = {{"a"}, {"<<"}, {"b"}};
	while (temp)
	{
		expect = array27[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("a<<b");
	temp = head;
	char	array28[][100] = {{"a"}, {"<<"}, {"b"}};
	while (temp)
	{
		expect = array28[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list(">>");
	temp = head;
	char	array29[][100] = {{">>"}};
	while (temp)
	{
		expect = array29[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("a >> b");
	temp = head;
	char	array30[][100] = {{"a"}, {">>"}, {"b"}};
	while (temp)
	{
		expect = array30[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("a>>b");
	temp = head;
	char	array31[][100] = {{"a"}, {">>"}, {"b"}};
	while (temp)
	{
		expect = array31[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	// tab
	i = 0;
	head = create_token_list("a\tb");
	temp = head;
	char	array32[][100] = {{"a"}, {"b"}};
	while (temp)
	{
		expect = array32[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);
	i = 0;
	head = create_token_list("\tab");
	temp = head;
	char	array33[][100] = {{"ab"}};
	while (temp)
	{
		expect = array33[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("ab\t");
	temp = head;
	char	array34[][100] = {{"ab"}};
	while (temp)
	{
		expect = array34[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);
	// new line

	i = 0;
	head = create_token_list("a\nb");
	temp = head;
	char	array35[][100] = {{"a"}, {"b"}};
	while (temp)
	{
		expect = array35[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);
	i = 0;
	head = create_token_list("\nab");
	temp = head;
	char	array36[][100] = {{"ab"}};
	while (temp)
	{
		expect = array36[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("ab\n");
	temp = head;
	char	array37[][100] = {{"ab"}};
	while (temp)
	{
		expect = array37[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	// space
	i = 0;
	head = create_token_list("      ab");
	temp = head;
	char	array38[][100] = {{"ab"}};
	while (temp)
	{
		expect = array38[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("ab      ");
	temp = head;
	char	array39[][100] = {{"ab"}};
	while (temp)
	{
		expect = array39[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	i = 0;
	head = create_token_list("a       b");
	temp = head;
	char	array40[][100] = {{"a"}, {"b"}};
	while (temp)
	{
		expect = array40[i];
		assert(strncmp(temp->word, expect, (int)strlen(temp->word)) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	return (0);
}
