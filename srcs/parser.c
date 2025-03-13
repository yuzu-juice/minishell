/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:22:31 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/13 12:33:23 by yohatana         ###   ########.fr       */
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
// char	*create_quarte_word(char *word, int start, char *line, int new_flg, t_token *head);
int create_quarte_word(char *word, int start, char *line, int new_flg, t_token **head);
t_token	*get_last_token(t_token **head);

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
	t_token	*head;

	int	i = 0;
	int	j = 0;
	space_flg = 0;
	len = (int)ft_strlen(line);
	int	word_len = 0;
	// 最初のスペースはスキップする
	if (line[0] == ' ')
	{
		while (line[i] == ' ')
			i++;
	}
	while (line[i])
	{
		if (line[i] == '\t' || line[i] == '\n')
		{
			// 区切りとして認識する
			// 連続することあるのか？
		}
		else if (line[i] == ' ')
		{
			if (space_flg != 1)
			{
				space_flg = 1;
				new_token_flg = 1;
			}
		}
		else if (line[i] == '|')
		{
			new_token_flg = 1;
			word = ft_strdup("|");
			add_token(&head, create_token_node(word));
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
				if (i == 0 || line[i - 1] == ' ' || line[i - 1] == '|')
					new_token_flg = 1;
				else
					new_token_flg = 0;
				word_len = create_quarte_word(word, i, line, new_token_flg, &head);
				i = i + word_len - 1;
			}
			else
			{
				j = i;
				while (line[j] != ' ' && line[j] != '|' && j < len)
					j++;
				word = create_token_word(i, j, line);
				i = j - 1;
				add_token(&head, create_token_node(word));
			}
		}
		i++;
	}

	printf("==== token node check ====\n");
	t_token *temp;
	temp = head;
	for (int k = 0;temp !=NULL; k++)
	{
		printf("word %s\n", temp->word);
		temp = temp->next;
	}

	// token listが出来たらコマンドリストを作る
}

t_token	*get_last_token(t_token **head)
{
	t_token	*temp;

	temp = *head;
	while (temp->next)
		temp = temp->next;
	return (temp);
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

int	create_quarte_word(char *word, int start, char *line, int new_flg, t_token **head)
{
	int		i;
	char	type;
	char	*splited;
	char	*temp = NULL;
	int		len;
	(void)word;
	t_token	*last;

	type = line[start];
	i = 1;
	while (line[i + start] != type && line[i + start])
	{
		i++;
	}
	splited = ft_substr(line, start, i + 1);
	// if (!splited)
	// 	return (NULL);
	len = (int)ft_strlen(splited);

	if (new_flg != 1)
	{
		last = get_last_token(head);
		// if (!temp)
		// 	return (NULL);
		temp = ft_strjoin(last->word, splited);
		free(last->word);
		free(splited);
		last->word = temp;
	}
	else
	{
		add_token(head, create_token_node(splited));
	}
	return (len);
}

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

	printf("");

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
