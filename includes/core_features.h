/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_features.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:31:13 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/13 13:32:58 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_FEATURES_H
# define CORE_FEATURES_H

# include <stdbool.h>
# include "env.h"
# include "redirections.h"

typedef struct s_token		t_token;
typedef struct s_proc		t_proc;
typedef struct s_minishell	t_minishell;

typedef struct s_token
{
	char	*word;
	t_token	*next;
}	t_token;

typedef struct s_proc
{
	char			*cmd;
	t_redirection	*redir;
	int				index;
	t_proc			*next;
}	t_proc;

// void		exec_cmd(t_minishell *m_shell, char *str, int proc_index);
// void	exec_cmd(t_minishell *m_shell, \
// 	char *cmd, \
// 	int proc_index, \
// 	int pipe_fd[2][2]);

// from envp
char	*get_env_pwd(void);
char	**get_env_path(void);

// create cmd
// char	*create_cmd_path(char *cmd);

// parser
bool	parser(char *line, t_minishell *m_shell);
bool	has_unclosed_quotes(char *line);

// expand_dollar
bool	expand_dollar(t_token **head, t_env *env);

// expand_dollar_util
bool	replace_word(t_token *curr, int *index, t_env replace);
char	*serch_env_value(char *key, t_env *env);

// create_token_list
t_token	*create_token_list(char *line);
t_token	*get_last_token(t_token **head);
void	free_token_list(t_token **head);
bool	create_split_token(char *line, int *index, t_token **head);
bool	create_normal_token(char *line, int *i, t_token **head);

// token util
bool	add_current_token(char *word, t_token **head);
t_token	*create_token_node(char *word);
bool	add_token_node(t_token **head, t_token *new);
bool	is_split_char(char c);
bool	is_quote(char c);

// create_process_list
t_proc	*create_process_list(t_token **head);

// create_process_list_util
bool	validation_pipe(t_token *prev, t_token *next);
t_proc	*get_last_proc(t_proc **list);
bool	add_space(t_proc *curr);
void	*free_proc_list(t_proc **list);

// error
void	syntax_error(t_token **head);

#endif
