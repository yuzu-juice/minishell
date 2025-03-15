/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_features.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:31:13 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/15 15:58:57 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_FEATURES_H
# define CORE_FEATURES_H

# include <stdbool.h>

typedef struct s_token t_token;

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
void		parser(char *line);
t_token		*create_token_list(char *line);
void		syntax_error(void);
bool		validation_quart(char *line);

// tokeniser
// int			create_quart_word(int *start, \
// 								char *line, \
// 								t_token **head);
t_token		*get_last_token(t_token **head);
t_token		*create_token_node(char *word);
char		*create_token_word(int *start, char *line, t_token **head);
void		add_token(t_token **head, t_token *new);

bool	is_split_char(char c);
bool	is_quart(char c);

#endif
