/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:22:31 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/10 19:42:32 by yohatana         ###   ########.fr       */
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
	t_token	*next;
}	t_token;

t_token		*create_token_node(char *word);
void		add_token(t_token **head, t_token *new);
static char	*create_token_word(int start, int end, char *line);
void		syntax_error(void);

// 空白区切りのみ許容します！！！！！！！
// ゴミを読み込んでるので初期化すること
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
	while (i < (int)ft_strlen(line))
	{
		if (line[i] != ' ')
		{
			if (line[i] == '\'')
			{
				j = i + 1;
				while (line[j] != '\'')
					j++;
				if (line[j] == '\'' && j < (int)ft_strlen(line))
				{
					word = create_token_word(i, j , line);
					add_token(&token_head, create_token_node(word));
					i = j;
				}
				if (j == (int)ft_strlen(line))
					syntax_error();
			}
			else if (line[i] == '\"')
			{
				j = i + 1;
				while (line[j] != '\"')
					j++;
				if (line[j] == '\"')
				{
					word = create_token_word(i, j , line);
					add_token(&token_head, create_token_node(word));
					i = j;
				}
				if (j == (int)ft_strlen(line))
					syntax_error();
			}
			else
			{
				j = i;
				while ((line[j] != ' ' && line[j] != '|') && line[j] != '\0' )
					j++;
				word = create_token_word(i, j, line);
				add_token(&token_head, create_token_node(word));
				i = j;
			}
		}

		// こっちはあと
		/*
		// pipeを先にやる
		else if (line[i] == '|')
		{
			word = create_token_word(i, i , line);
			add_token(&token_head, create_token_node(word));
		}
		*/
		i++;
	}

/* 確認用 */
	printf("=== token list check ===\n");
	t_token *test;
	test = token_head;
	while (test)
	{
		printf("word :%s\n", test->word);
		test = test->next;
	}
}

static char	*create_token_word(int start, int end, char *line)
{
	char	*word;
	int		i;

	printf("s :%d e :%d\n", start, end);
	word = (char *)ft_calloc(sizeof(char), end - start + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i + start <= end)
	{
		word[i] = line[i + start];
		i++;
	}
	return (word);
}

t_token	*create_token_node(char *word)
{
	t_token	*token;

	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL); // TODO error
	token->word = word;
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

/*
int	main(void)
{
	// 加工なし
	parser(0, NULL, "echo");
	parser(0, NULL, "echo hello");
	parser(0, NULL, "");

	// single quarte
	parser(0, NULL, "'aaa'"); // aaa
	parser(0, NULL, "'aaa' 'bbb'"); // aaa bbb
	parser(0, NULL, "echo 'hello'"); // hello
	parser(0, NULL, "echo'hello'"); // echohello
	parser(0, NULL, "echo '$PWD'"); // ＄PWD
	parser(0, NULL, "'echo $PWD'"); // echo ＄PWD
	parser(0, NULL, "'echo \"aaa $PWD\"'"); // echo "aaa $PWD"

	// duoble quarte
	parser(0, NULL, "\"aaa\"");
	parser(0, NULL, "\"aaa\" \"bbb\"");
	parser(0, NULL, "echo \"hello\""); // hello
	parser(0, NULL, "echo\"hello\""); // echohello
	parser(0, NULL, "echo \"$PWD\""); // work//minishell
	parser(0, NULL, "\"echo $PWD\""); // work//minishell
	parser(0, NULL, "echo \"hello 'world'\""); // hello 'world'

	// これがどうなる？
	parser(0, NULL, echo "hello'world$PWD'$PWD"); //

	// yohatana@c3r5s1:~/work/minishell$ echo hello'world''$PWD'"$PWD"
	// helloworld$PWD/home/yohatana/work/minishell

	return (0);
}
*/
