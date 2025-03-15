/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:48:17 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/15 16:04:17 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

// static int	create_redirect_token(char *line, int *i, t_token **head);
bool	create_normal_token(char *line, int *i, t_token **head);
bool		create_split_token(char *line, int *index, t_token **head);
static bool	create_redirect_token(char *line, int *i, t_token **head);
bool	create_double_redirect(char *line, int *index, char **word);
bool	create_quart_word(char *line, int *index, t_token **head);

t_token	*create_token_list(char *line)
{
	t_token	*head;
	int		index;
	bool	err_flg;

	index = 0;
	head = NULL;
	while (line[index])
	{
		if (is_split_char(line[index]))
			err_flg = create_split_token(line, &index, &head);
		else
			err_flg = create_normal_token(line, &index, &head);
		if (err_flg)
			break ;
	}
	printf("==== token node check ====\n");
	t_token *temp;
	temp = head;
	for (int k = 0;temp !=NULL; k++)
	{
		printf("word %s\n", temp->word);
		temp = temp->next;
	}
	if (err_flg)
		syntax_error();
	return (head);
}

bool	create_split_token(char *line, int *index, t_token **head)
{
	bool	err_flg;
	char	*word;

	err_flg = 0;
	if (line[*index] == '|')
	{
		word = ft_strdup("|");
		if (!word)
			err_flg = true;
		add_token(head, create_token_node(word));
		*index = *index + 1;
	}
	else if (line[*index] == '<' || line[*index] == '>')
		err_flg = create_redirect_token(line, index, head);
	else
		*index = *index + 1;
	return (err_flg);
}

static bool	create_redirect_token(char *line, int *i, t_token **head)
{
	char	*word;
	int		new_token_flg;
	bool	err_flg;

	printf("i %d line[i] %c\n", *i, line[*i]);
	err_flg = false;
	new_token_flg = 1;
	if (line[*i] == '<')
		word = ft_strdup("<");
	else
		word = ft_strdup(">");
	if (!word)
		err_flg = true;
	if (err_flg)
		return (err_flg);
	err_flg = create_double_redirect(line, i, &word);
	add_token(head, create_token_node(word));
	*i = *i + 1;
	printf("i %d\n", *i);
	return (err_flg);
}

bool	create_double_redirect(char *line, int *index, char **word)
{
	bool	err_flg;
	char	type;
	char	*temp;

	err_flg = false;
	type = line[*index];
	if (line[*index + 1] == type)
	{
		temp = ft_strjoin(*word, *word);
		if (!temp)
			err_flg = true;
		free(*word);
		*word = temp;
		*index = *index + 1;
	}
	return (err_flg);
}

bool	create_normal_token(char *line, int *i, t_token **head)
{
	int		word_len;
	int		len;
	bool	err_flg;
	(void)head;

	err_flg = false;
	word_len = 0;
	len = (int)ft_strlen(line);
	if (is_quart(line[*i]))
	{
		printf("is quart\n");
		err_flg = create_quart_word(line, i, head);
	}
	else
	{
		printf("normal char\n");
		// create_token_word(i, line, head);
	}
	return (err_flg);
}

bool	create_quart_word(char *line, int *index, t_token **head)
{
	bool	err_flg;
	int		j;
	char	type;
	char	*word;

	type = line[*index];
	j = 1;
	while (line[*index + j] != type)
		j++;
	word = ft_substr(line, *index, j);
	if (!word)
	{
		err_flg = true;
	}
	err_flg = false;
	return (err_flg);
}



























// void	create_token_list(char *line, t_token **head)
// {
// 	char	*word;
// 	int		i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (is_split_char(line[i]))
// 		{
// 			if (line[i] == '|')
// 			{
// 				word = ft_strdup("|");
// 				// 戻り値でエラーか判定する
// 				add_token(head, create_token_node(word));
// 			}
// 			else if (line[i] == '>' || line[i] == '<')
// 				create_redirect_token(line, &i, head);
// 			i++;
// 		}
// 		else
// 		{
// 			create_normal_token(line, &i, head);
// 		}
// 	}

// 	printf("==== token node check ====\n");
// 	t_token *temp;
// 	temp = *head;
// 	for (int k = 0;temp !=NULL; k++)
// 	{
// 		printf("word %s\n", temp->word);
// 		temp = temp->next;
// 	}
// }

// int	create_quart_word(int *start, char *line, t_token **head)
// {
// 	int		i;
// 	char	type;
// 	char	*splited;
// 	char	*temp = NULL;
// 	int		len;
// 	int		new_token_flg;
// 	t_token	*last;

// 	new_token_flg = 0;
// 	if (*start == 0 || is_split_char(line[*start - 1]))
// 		new_token_flg = 1;
// 	else
// 		new_token_flg = 0;
// 	type = line[*start];
// 	i = 1;
// 	while (line[i + *start] != type && line[i + *start] != '\0')
// 		i++;
// 	splited = ft_substr(line, *start, i + 1);
// 	if (!splited)
// 		return (0);
// 	len = (int)ft_strlen(splited);
// 	if (new_token_flg == 0)
// 	{
// 		last = get_last_token(head);
// 		temp = ft_strjoin(last->word, splited);
// 		if (!temp)
// 			return (0);
// 		free(last->word);
// 		free(splited);
// 		last->word = temp;
// 	}
// 	else
// 		add_token(head, create_token_node(splited));
// 	*start = *start + i;
// 	return (len);
// }


