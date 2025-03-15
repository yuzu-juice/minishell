/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:48:17 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/14 19:15:43 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

static int	create_redirect_token(char *line, int *i, t_token **head);
void	create_normal_token(char *line, int *i, t_token **head);

void	create_token_list(char *line, t_token **head)
{
	char	*word;
	int		i;

	i = 0;
	while (line[i])
	{
		if (is_split_char(line[i]))
		{
			if (line[i] == '|')
			{
				word = ft_strdup("|");
				// 戻り値でエラーか判定する
				add_token(head, create_token_node(word));
			}
			else if (line[i] == '>' || line[i] == '<')
				create_redirect_token(line, &i, head);
			i++;
		}
		else
		{
			create_normal_token(line, &i, head);
		}
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

int	create_quart_word(int *start, char *line, t_token **head)
{
	int		i;
	char	type;
	char	*splited;
	char	*temp = NULL;
	int		len;
	int		new_token_flg;
	t_token	*last;

	new_token_flg = 0;
	if (*start == 0 || is_split_char(line[*start - 1]))
		new_token_flg = 1;
	else
		new_token_flg = 0;
	type = line[*start];
	i = 1;
	while (line[i + *start] != type && line[i + *start] != '\0')
		i++;
	splited = ft_substr(line, *start, i + 1);
	if (!splited)
		return (0);
	len = (int)ft_strlen(splited);
	if (new_token_flg == 0)
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
	*start = *start + i;
	return (len);
}

void	create_normal_token(char *line, int *i, t_token **head)
{
	int		word_len;
	int		len;

	word_len = 0;
	len = (int)ft_strlen(line);
	if (is_quart(line[*i]))
	{
		word_len = create_quart_word(i, line, head);
	}
	else
	{
		create_token_word(i, line, head);
	}
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
