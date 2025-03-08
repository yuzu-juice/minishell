/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:22:31 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/08 17:54:10 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"
/*
このコマンドを入力したとする
$ ls | wc -l | echo ${HOGE} | sed 's/aaa/bbb/'


次のような構造体にコマンドを分割して入れるイメージ。
typedef struct s_cmd
{
  char *cmd;
  char **args;
  char *cmd_abs_path;
} t_cmd

↓cmdをlistで持つ
typedef struct cmds
{
  t_cmd cmd;
  t_cmd *next;
} t_cmds


Step1. まず "|" と " " でsplitする
t_cmd
{
  char *cmd = "ls";
  char **args = NULL;
  char *cmd_abs_path = <lsの絶対パス>;
}

t_cmd
{
  char *cmd = "wc";
  char **args = ["-l"];
  char *cmd_abs_path = <wcの絶対パス>;
}

t_cmd
{
  char *cmd = "echo";
  char **args = ["${HOGE}"]; <- まだ展開せずに文字列で持つ
  char *cmd_abs_path = <echoの絶対パス>;
}

t_cmd
{
  char *cmd = "sed";
  char **args = "['s/aaa/bbb/'"];
  char *cmd_abs_path = <sedの絶対パス>;
}


Step2. single quote, double quoteを消す
t_cmd
{
  char *cmd = "sed";
  char **args = ["s/aaa/bbb/"]; <- single quote消した
  char *cmd_abs_path = <sedの絶対パス>;
}


Step3. 環境変数の展開
t_cmd
{
  char *cmd = "echo";
  char **args = ["expanded_var"]; <- 展開した
  char *cmd_abs_path = <echoの絶対パス>;
}

*/

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	char	*cmd_abs_path;
	int		status;
} t_cmd;

typedef struct s_fds
{
	int	in;
	int	out;
}	t_fds;

typedef struct s_cmd_list
{
	t_cmd	cmd;
	t_cmd	*next;
}	t_cmd_list;

typedef struct s_tokens
{
	char		*token;
	t_tokens	*next;
}	t_tokens;

static char	*single_token(int start, int end, char *line);

void	parser(int argc, char **envp, char *line)
{
	(void)argc;
	(void)envp;

	// char	**splited;
	// char	*no_single;
	int		i;
	char	*token;			// 1かたまり
	int		token_count;

	// char	**token_array; // 最終的に入れる

	int		j;
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			j = i + 1;
			while (line[j] != '\'')
				j++;
			if (line[j] == '\'')
			{
				token = single_token(i + 1, j , line);
				i = j;
				token_count++;
			}
		}
		i++;
	}

	// ""　ダブル($展開をする)

	// |　パイプ

	// $ 展開
}

static char	*single_token(int start, int end, char *line)
{
	char	*token;
	int		i;

	printf("s :%d e :%d\n", start, end);
	token = (char *)ft_calloc(sizeof(char), end - start + 1);
	if (!token)
		return (NULL);
	i = 0;
	while (i + start < end)
	{
		token[i] = line[i + start];
		i++;
	}
	printf("token %s\n", token);
	return (token);
}

t_tokens	*create_token_node(char *word)
{
	t_tokens	*token;

	token = (t_tokens *)ft_calloc(sizeof(t_tokens), 1);
	if (!token)
		return (NULL); // TODO error
	token->token = word;
	token->next = NULL;
}
