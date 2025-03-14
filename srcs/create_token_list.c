/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:48:17 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/14 16:12:38 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

static int	create_redirect_token(char *line, int *i, t_token **head);
static bool	is_split_char(char c);
static bool	is_quart(char c);
void	create_normal_token(char *line, int *i, t_token **head);

void	create_token_list(char *line, t_token **head)
{
	int		new_token_flg = 0;
	int		len;
	char	*word;
	char	*temp_word;
	int		i;
	int		j;
	// int	word_len;

	i = 0;
	j = 0;
	// word_len = 0;
	len = (int)ft_strlen(line);
	if (line[0] == ' ')
	{
		while (line[i] == ' ')
			i++;
	}
	while (line[i])
	{
		if (is_split_char(line[i]))
		{
			// if (line[i] == '\t' || line[i] == '\n' || line[i] == ' ')
			// 	new_token_flg = 1;
			if (line[i] == '|')
			{
				new_token_flg = 1;
				word = ft_strdup("|");
				add_token(head, create_token_node(word));
			}
			else if (line[i] == '>' || line[i] == '<')
				create_redirect_token(line, &i, head);
		}
		else
		{
			create_normal_token(line, &i, head);
			// if (is_quart(line[i]))
			// {
			// 	if (i == 0 || is_split_char(line[i - 1]))
			// 		new_token_flg = 1;
			// 	else
			// 		new_token_flg = 0;
			// 	word_len = create_quart_word(i, line, new_token_flg, head);
			// 	i = i + word_len - 1;
			// }
			// else
			// {
				j = i;
				if (i != 0 && (line[i - 1] == '\'' || line[i - 1] == '\"'))
					new_token_flg = 0;
				else
					new_token_flg = 1;
				while (!is_split_char(line[j]) && !is_quart(line[j]) && j < len)
					j++;
				word = create_token_word(i, j, line);
				i = j - 1;
				if (new_token_flg == 0)
				{
					// quartのところと共通化できそう
					temp_word = ft_strjoin(get_last_token(head)->word, word);
					free(get_last_token(head)->word);
					free(word);
					get_last_token(head)->word = temp_word;
				}
				else
					add_token(head, create_token_node(word));
			// }
		}
		i++;
	}

	printf("==== token node check ====\n");
	t_token *temp;
	temp = *head;
	for (int k = 0;temp !=NULL; k++)
	{
		printf("word %s\n", temp->word);
		temp = temp->next;
	}
}

static bool	is_split_char(char c)
{
	if (c == ' ' || c == '|' || c == '\t' || c == '\n' || c == '>' || c == '<')
		return (true);
	return (false);
}

static bool	is_quart(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

int	create_quart_word(int start, char *line, int new_flg, t_token **head)
{
	int		i;
	char	type;
	char	*splited;
	char	*temp = NULL;
	int		len;
	t_token	*last;

	type = line[start];
	i = 1;
	while (line[i + start] != type)
	{
		i++;
	}
	splited = ft_substr(line, start, i + 1);
	if (!splited)
		return (0);
	len = (int)ft_strlen(splited);
	if (new_flg == 0)
	{
		last = get_last_token(head);
		temp = ft_strjoin(last->word, splited);
		if (!temp)
			return (0);
		free(last->word);
		free(splited);
		last->word = temp;
	}
	else
		add_token(head, create_token_node(splited));
	return (len);
}

void	create_normal_token(char *line, int *i, t_token **head)
{
	// char	*word;
	int		new_token_flg;
	int		word_len;
	int		len;
	// char	*temp_word;
	// int		j;

	new_token_flg = 0;
	word_len = 0;
	// j = 0;
	len = 0;
	// インデックスのポインタが終わりになっているよーん＾＾
	printf("*i %d line[*i] %c\n", *i, line[*i]);
	if (is_quart(line[*i]))
	{
		if (*i == 0 || is_split_char(line[*i - 1]))
			new_token_flg = 1;
		else
			new_token_flg = 0;
		word_len = create_quart_word(*i, line, new_token_flg, head);
		*i = *i + word_len - 1;
	}
	// else
	// {
	// 	j = *i;
	// 	if (*i != 0 && (line[*i - 1] == '\'' || line[*i - 1] == '\"'))
	// 		new_token_flg = 0;
	// 	else
	// 		new_token_flg = 1;
	// 	while (!is_split_char(line[j]) && !is_quart(line[j]) && j < len)
	// 		j++;
	// 	word = create_token_word(*i, j, line);
	// 	printf("word %s\n", word);
	// 	*i = j - 1;
	// 	if (new_token_flg == 0)
	// 	{
	// 		// quartのところと共通化できそう
	// 		temp_word = ft_strjoin(get_last_token(head)->word, word);
	// 		free(get_last_token(head)->word);
	// 		free(word);
	// 		get_last_token(head)->word = temp_word;
	// 	}
	// 	else
	// 		add_token(head, create_token_node(word));
	// }
}

// return 0 is success
static int	create_redirect_token(char *line, int *i, t_token **head)
{
	char	*word;
	char	type;
	int		new_token_flg;
	char	*temp;

	type = line[*i];
	new_token_flg = 1;
	if (line[*i] == '>')
		word = ft_strdup(">");
	else
		word = ft_strdup("<");
	if (line[*i + 1] == type)
	{
		temp = ft_strjoin(word, word);
		free(word);
		word = temp;
		*i = *i + 1;
	}
	add_token(head, create_token_node(word));
	return (0);
}
