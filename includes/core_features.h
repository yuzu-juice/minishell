/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_features.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:31:13 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/26 16:46:50 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_FEATURES_H
# define CORE_FEATURES_H

# include <stdbool.h>
# include "env.h"

typedef struct s_token		t_token;
typedef struct s_proc_list	t_proc_list;

typedef struct s_token
{
	char	*word;
	t_token	*next;
}	t_token;

typedef struct s_proc
{
	char	*cmd;
	int		status;
}	t_proc;

typedef struct s_proc_list
{
	t_proc		*proc;
	t_proc_list	*next;
}	t_proc_list;

void		exec_cmd(t_env *env, char *str);

// from envp
char		*get_env_pwd(void);
char		**get_env_path(void);

// create cmd
char		*create_cmd_path(char *cmd);

// parser
bool		parser(char *line);
void		expand(t_token **head);
bool		has_unclosed_quotes(char *line);

// create_token_list
t_token		*create_token_list(char *line);
t_token		*get_last_token(t_token **head);
void		free_token_list(t_token **head);
bool		create_split_token(char *line, int *index, t_token **head);
bool		create_normal_token(char *line, int *i, t_token **head);

// token util
bool		add_current_token(char *word, t_token **head);
t_token		*create_token_node(char *word);
bool		add_token_node(t_token **head, t_token *new);
bool		is_split_char(char c);
bool		is_quote(char c);

// create_process_list
t_proc_list	*create_process_list(t_token **head);
bool		add_space(t_proc_list *curr);
t_proc_list	*get_last_proc(t_proc_list **list);
bool		validation_pipe(t_token *prev, t_token *next);

// error
void		syntax_error(t_token **head);

#endif
