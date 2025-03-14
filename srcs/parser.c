/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:22:31 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/14 15:45:30 by yohatana         ###   ########.fr       */
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

void	parser(char *line)
{
	t_token	*head;
	// lineが長すぎる場合はここでエラー返す

	head = NULL;
	if (validation_quart(line))
		syntax_error();
// ============ OK =========================
	create_token_list(line, &head);
	// expansion()
	// quart_trim()
	// create_cmds()
	// free_token_list()

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

void	free_token_list(t_token **head)
{
	t_token	*curr;
	t_token	*temp;

	if (head == NULL)
		return ;
	curr = *head;
	while (curr)
	{
		temp = curr->next;
		free(curr->word);
		free(curr);
		curr = temp;
	}
}

bool	validation_quart(char *line)
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
				return (true);
			i = j;
		}
		i++;
	}
	return (false);
}

void	syntax_error(void)
{
	perror("syntax_error");
	// free token
	// free cmd
}
