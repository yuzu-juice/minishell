/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_features.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:31:13 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/16 16:45:26 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_FEATURES_H
# define CORE_FEATURES_H

# include <stdbool.h>

typedef struct s_token	t_token;

typedef struct s_token
{
	char	*word;
	t_token	*next;
}	t_token;

void		exec_cmd(char **envp, char *str);

// from envp
char		*get_env_pwd(void);
char		**get_env_path(void);

// create cmd
char		*create_cmd_path(char *cmd);

// parser
bool		parser(char *line);
t_token		*create_token_list(char *line);
void		expansion(t_token **head);
bool		validation_quart(char *line);

bool		create_split_token(char *line, int *index, t_token **head);
t_token		*create_token_node(char *word);
bool		create_token_word(int *start, char *line, t_token **head);
bool		add_token(t_token **head, t_token *new);
bool		add_current_token(char *word, t_token **head);
bool		create_normal_token(char *line, int *i, t_token **head);
bool		create_quart_word(char *line, int *index, t_token **head);

// token util
bool		is_split_char(char c);
bool		is_quart(char c);
t_token		*get_last_token(t_token **head);
void		free_token_list(t_token **head);

// error
void		syntax_error(t_token **head);
void		print_msg(char *str);

#endif
