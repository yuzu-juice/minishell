/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_features.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:31:13 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/20 19:24:14 by yohatana         ###   ########.fr       */
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
	char			**cmd_args;
	t_redirection	*redir;
	int				index;
	t_proc			*next;
}	t_proc;

// from envp
char				*get_env_pwd(void);
char				**get_env_path(t_minishell *m_shell);

// parser
bool				parser(char *line, t_minishell *m_shell);
bool				has_unclosed_quotes(char *line);
t_proc				*create_process_list(t_token **head);
t_proc				*create_proc_node(char *word);
bool				add_proc_list(t_proc **list, t_proc *new);
bool				add_to_cmd(t_proc **list, char *word, bool is_new_proc);

// parser redirection
bool				is_redirection(char *word);
t_redirection_type	get_redirection_type(char *word);
bool				add_redirection(
						t_proc *proc,
						t_redirection_type type,
						char *filename
						);

// expand_dollar
bool				expand_dollar(t_token **head, t_minishell *m_shell);

// expand_dollar_util
bool				replace_word(t_token *curr, int *index, t_env replace);
char				*search_env_value(char *key, t_minishell *m_shell);

// create_token_list
t_token				*create_token_list(char *line);
t_token				*get_last_token(t_token **head);
void				free_token_list(t_token **head);
bool				create_split_token(char *line, int *index, t_token **head);
bool				create_normal_token(char *line, int *i, t_token **head);

// token util
bool				add_current_token(char *word, t_token **head);
t_token				*create_token_node(char *word);
bool				add_token_node(t_token **head, t_token *new);
bool				is_split_char(char c);
bool				is_quote(char c);
int					count_token(t_token **head);

// create_process_list
t_proc				*create_process_list(t_token **head);

// create_process_list_util
bool				validation_pipe(t_token *prev, \
									t_token *next, \
									t_proc **list);
t_proc				*get_last_proc(t_proc **list);
bool				add_space(t_proc *curr);
void				*free_proc_list(t_proc **list);

// error
void				syntax_error(t_token **head);

#endif
