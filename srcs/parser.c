/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:22:31 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/09 17:54:43 by yohatana         ###   ########.fr       */
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
	char	*quart_del_line;

	token_head = NULL;
	i = 0;
	j = 0;
	int	expansion_flg = 0;
	while (i < (int)ft_strlen(line))
	{
		// echo"aaa"のときは別のtokenにしちゃうとまずい（ゆたtips）
		// のでいっかいクォートを削除するほうが丸いと思った
		// tokenのwordに入れはするが、これ単体では入れない

		// $展開をすべて後回しにすると、シングルでも展開されてしまう
		// token→wordに入れた時点では、完全な文字列にしなくてはいけない

		// bash manual tokanizerを参照
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
			if (j == (int)ft_strlen(line))
			{
				syntax_error();
			}
			// 次の文字が空白かパイプ以外ならwordにstrjoinする
			if (line[i + 1] != ' ' || line[i + 1] != '|' )
			{
				j = i + 1;
				while (line[j] != '\'')
					j++;
				if (line[j] == '\'' && j < (int)ft_strlen(line))
				{
					word = quart_token(i + 1, j , line);
					// last node->word = ft_strjoin(node->word, word);
					// add_token(&token_head, create_token_node(word, expansion_flg));
					i = j;
				}
			}
		}
		// else if (line[i] == '\"')
		// {
		// 	j = i + 1;
		// 	while (line[j] != '\"')
		// 		j++;
		// 	if (line[j] == '\"')
		// 	{
		// 		word = quart_token(i + 1, j , line);
		// 		expansion_flg = 1;
		// 		add_token(&token_head, create_token_node(word, expansion_flg));
		// 		i = j;
		// 	}
		// 	if (j == (int)ft_strlen(line))
		// 	{
		// 		syntax_error();
		// 	}
		// }
		// pipeを先にやる
		else if (line[i] == '|')
		{
			// create token
			// word = "|"
		}
		else if (line[i] == '$')
		{
			// ' ' '\'' "\""が来るまでtokenとして扱う
		}
		else
		{
			j = i;
			while ((line[j] != ' ' && line[j] != '\'' \
			&& line[j] != '\"' && line[j] != '$'\
			&& line[j] != '|') && line[j] != '\0' )
			{
				j++;
			}
			word = quart_token(i, j , line);
			add_token(&token_head, create_token_node(word, expansion_flg));
			i = j - 1;
		}
		i++;
	}

/* 確認用 */
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
	return (0);
}
*/
