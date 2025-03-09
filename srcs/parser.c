/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:22:31 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/09 15:30:02 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	char	*cmd_abs_path;
	int		status;
} t_cmd;

typedef struct s_cmd_list
{
	t_cmd	cmd;
	t_cmd	*next;
}	t_cmd_list;

typedef struct s_token t_token;

typedef struct s_token
{
	char	*word;
	int		expansion_flg;
	t_token	*next;
}	t_token;

t_token		*create_token_node(char *word, int expansion_flg);
void		add_token(t_token **head, t_token *new);
static char	*quart_token(int start, int end, char *line);
void		syntax_error(void);

void	parser(int argc, char **envp, char *line)
{
	(void)argc;
	(void)envp;
	(void)line;

	int		i;
	int		j;
	char	*word;
	t_token	*token_head;

	token_head = NULL;
	i = 0;
	j = 0;
	int	expansion_flg = 0;
	while (line[i])
	{
		// 'が奇数のときはエラーにする
		if (line[i] == '\'')
		{
			j = i + 1;
			while (line[j] != '\'')
				j++;
			if (line[j] == '\'' && j < (int)ft_strlen(line))
			{
				word = quart_token(i + 1, j , line);
				add_token(&token_head, create_token_node(word, expansion_flg));
				i = j;
			}
			// if (j == (int)ft_strlen(line))
			// {
			// 	// syntax_error()
			// }
		}
		if (line[i] == '\"')
		{
			j = i + 1;
			while (line[j] != '\"')
				j++;
			if (line[j] == '\"')
			{
				word = quart_token(i + 1, j , line);
				expansion_flg = 1;syntax errorode(word, expansion_flg));
				i = j;
			}
		}
		if (line[i] == '|')
		{
			// create token
			// word = "|"
		}
		if (line[i] == '$')
		{
			// ' ' '\'' "\""が来るまでtokenとして扱う
		}

		if (line[i] == ' ')
		{
			if (line[i - 1] != ' ' || line[i - 1] == '\'' || line[i - 1] == '\"')
			{
				// create token
			}
		}
		i++;
	}

	printf("=== token list check ===\n");
	t_token *test;
	test = token_head;
	while (test)
	{
		printf("word :%s expansion flg :%d\n", test->word, test->expansion_flg);
		test = test->next;
	}

	// '|'が来るまでは連結する
	// '|'の前後にtokenがない場合(> ,'', "", $, stringはtokenになる)

}

static char	*quart_token(int start, int end, char *line)
{
	char	*word;
	int		i;

	printf("s :%d e :%d\n", start, end);
	word = (char *)ft_calloc(sizeof(char), end - start + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i + start < end)
	{
		word[i] = line[i + start];
		i++;
	}
	return (word);
}

t_token	*create_token_node(char *word, int expansion_flg)
{
	t_token	*token;

	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL); // TODO error
	token->word = word;
	token->expansion_flg = expansion_flg;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new)
{
	t_token	*temp;

	if (*head == NULL)
	{
		*head = new;
	}
	else
	{
		temp = *head;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
}

void	syntax_error(void)
{
	perror("syntax_error");
	// free token
	// free cmd
}
