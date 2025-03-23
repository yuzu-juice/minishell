#include"../../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_env *env;
	t_token *head;
	bool	err;
	t_token *temp;
	int i = 0;

	env = envp_to_list(envp);

	// only 1 token 1 dollar
	char	array1[][100] = {{"/home/yohatana/work/minishell"}};
	head = create_token_list("$PWD");
	err = expand_dollar(&head, env);
	assert(err == false);
	temp = head;
	while (temp)
	{
		assert(strcmp(temp->word, array1[i]) == 0);
		temp = temp->next;
		i++;
	}
	free_token_list(&head);

	char	array2[][100] = {{"/home/yohatana/work/minishell/home/yohatana/work/minishell"}};
	head = create_token_list("$PWD$PWD");
	err = expand_dollar(&head, env);
	assert(err == false);
	temp = head;
	i = 0;
	while (temp)
	{
		assert(strcmp(temp->word, array2[i]) == 0);
		temp = temp->next;
		i++;
	}

	char	array3[][100] = {{"a/home/yohatana/work/minishell"}};
	head = create_token_list("a$PWD");
	err = expand_dollar(&head, env);
	assert(err == false);
	temp = head;
	i = 0;
	while (temp)
	{
		assert(strcmp(temp->word, array3[i]) == 0);
		temp = temp->next;
		i++;
	}

	// double quote
	char	array4[][100] = {{"\"/home/yohatana/work/minishell\""}};
	head = create_token_list("\"$PWD\"");
	err = expand_dollar(&head, env);
	assert(err == false);
	temp = head;
	i = 0;
	while (temp)
	{
		assert(strcmp(temp->word, array4[i]) == 0);
		temp = temp->next;
		i++;
	}

	// nothing env value
	char	array5[][100] = {{""}};
	head = create_token_list("$NOTHING");
	err = expand_dollar(&head, env);
	assert(err == false);
	temp = head;
	i = 0;
	while (temp)
	{
		assert(strcmp(temp->word, array5[i]) == 0);
		temp = temp->next;
		i++;
	}

	// single quote
	char	array6[][100] = {{"\'$PWD\'"}};
	head = create_token_list("\'$PWD\'");
	err = expand_dollar(&head, env);
	assert(err == false);
	temp = head;
	i = 0;
	while (temp)
	{
		assert(strcmp(temp->word, array6[i]) == 0);
		temp = temp->next;
		i++;
	}

	// 1 token 2 dollars
	char	array7[][100] = {{"/home/yohatana/work/minishell\"/home/yohatana/work/minishell\""}};
	head = create_token_list("$PWD\"$PWD\"");
	err = expand_dollar(&head, env);
	assert(err == false);
	temp = head;
	i = 0;
	while (temp)
	{
		assert(strcmp(temp->word, array7[i]) == 0);
		temp = temp->next;
		i++;
	}

	// $ only
	char	array8[][100] = {{"$"}};
	head = create_token_list("$");
	err = expand_dollar(&head, env);
	assert(err == false);
	temp = head;
	i = 0;
	while (temp)
	{
		assert(strcmp(temp->word, array8[i]) == 0);
		temp = temp->next;
		i++;
	}

	// contiguous string
	char	array9[][100] = {{"abc/home/yohatana/work/minishell\'def\'"}};
	head = create_token_list("abc$PWD\'def\'");
	err = expand_dollar(&head, env);
	assert(err == false);
	temp = head;
	i = 0;
	while (temp)
	{
		assert(strcmp(temp->word, array9[i]) == 0);
		temp = temp->next;
		i++;
	}

	// many token
	char	array10[][100] = {{"abc/home/yohatana/work/minishell\'def\'"}, {"\"yohatana\""}, {"yohatana"} ,{"\'$\'"}};
	head = create_token_list("abc$PWD\'def\' $a\"$USER\" $USER \'$\'");
	err = expand_dollar(&head, env);
	assert(err == false);
	temp = head;
	i = 0;
	while (temp)
	{
		assert(strcmp(temp->word, array10[i]) == 0);
		temp = temp->next;
		i++;
	}
	return (0);
}
