/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_features.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:31:13 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/28 14:46:25 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_FEATURES_H
# define CORE_FEATURES_H

# include <stdbool.h>
# include "env.h"
# include "redirections.h"

typedef struct s_token		t_token;
typedef struct s_proc_list	t_proc_list;
typedef struct s_proc		t_proc;

typedef struct s_token
{
	char	*word;
	t_token	*next;
}	t_token;

typedef struct s_proc
{
	char			*cmd;
	t_redirection	*redir;
	t_proc			*next;
}	t_proc;

void		exec_cmd(t_env **env, char *str);

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
t_proc		*create_process_list(t_token **head);

// create_process_list_util
bool		validation_pipe(t_token *prev, t_token *next);
t_proc		*get_last_proc(t_proc **list);
bool		add_space(t_proc *curr);
void		*free_proc_list(t_proc **list);

// error
void		syntax_error(t_token **head);

#endif
