/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:22:31 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/11 17:41:15 by yohatana         ###   ########.fr       */
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
void		syntax_error(void);
int			validation_quarte(char *line);
static char	*create_token_word(int start, int end, char *line);
char	*create_quarte_word(char *word, int start, char *line, int new_flg);

/*
man bash
DEFINITIONS
       The following definitions are used throughout the rest  of  this  document.
       blank  A space or tab.
       word   A  sequence  of  characters  considered  as a single unit by the
              shell.  Also known as a token.
       name   A word consisting only of  alphanumeric  characters  and  underscores,  and beginning with an alphabetic character or an underscore.  Also referred to as an identifier.
       metacharacter
              A character that, when unquoted, separates words.   One  of  the
              following:
              |  & ; ( ) < > space tab newline
       control operator
              A token that performs a control function.  It is one of the fol‐
              lowing symbols:
              || & && ; ;; ;& ;;& ( ) | |& <newline>
*/
void	parser(char *line)
{

	if (validation_quarte(line))
		syntax_error();
// ============ OK =========================

	int		new_token_flg = 0;
	int		len;
	char	*word;
	int		space_flg;

	int	i = 0;
	int	j = 0;
	space_flg = 0;
	len = (int)ft_strlen(line);
	while (line[i])
	{
		if (line[i] == '\t' || line[i] == '\n')
		{
			// 区切りとして認識する
			// 連続することあるのか？
		}
		else if (line[i] == ' ')
		{
			// 連続しているときはすっ飛ばす
			if (space_flg == 1)
				continue ;
			space_flg = 1;
			new_token_flg = 1;
		}
		else if (line[i] == '|')
		{
			new_token_flg = 1;
			word = ft_strdup("|");
			printf("word %s\n", word);
		}
		else if (line[i] == '>')
		{
			// > <
			// 後ろが同じか？
		}
		else
		{
			if (line[i] == '\'' || line[i] == '\"')
			{
				if (i == 0 || line[i - 1] == ' ')
					new_token_flg = 1;
				else
					new_token_flg = 0;
				word = create_quarte_word(word, i, line, new_token_flg);
				i = i + (int)ft_strlen(word) - 1;
			}
			else
			{
				j = i;
				while (line[j] != ' ' && line[j] != '|' && j < len)
					j++;
				word = create_token_word(i, j, line);
				i = j;
			}
			printf("word %s\n", word);
		}
		// wordが作成されたらノードを作成する
		t_token	*head;
		add_token(&head, create_token_node(word));
		i++;
	}

	// token listが出来たらコマンドリストを作る
}

int	validation_quarte(char *line)
{
	int		i;
	int		j;
	char	type;

	i = 0;
	j = 0;
	type = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (line[i] == '\'')
				type = '\'';
			if (line[i] == '\"')
				type = '\"';
			j = i + 1;
			while (line[j] != type && j < (int)ft_strlen(line))
				j++;
			if (j == (int)ft_strlen(line))
				return (1);
			i = j;
		}
		i++;
	}
	return (0);
}

char	*create_quarte_word(char *word, int start, char *line, int new_flg)
{
	int		i;
	char	type;
	char	*splited;
	char	*temp;

	type = line[start];
	i = start + 1;
	while (line[i + start] != type && line[i + start])
		i++;
	splited = ft_substr(line, start, i + 1);
	if (!splited)
		return (NULL);
	if (new_flg != 1)
	{
		temp = ft_strjoin(word, splited);
		if (!temp)
			return (NULL);
		free(word);
		free(splited);
		splited = temp;
	}
	return (splited);
}

// substrでやってみる
static char	*create_token_word(int start, int end, char *line)
{
	char	*word;

	word = ft_substr(line, start, end - start);
	if (!word)
		return (NULL);
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
