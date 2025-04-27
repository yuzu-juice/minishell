/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:25:30 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/27 11:46:55 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env	t_env;

typedef struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
}	t_env;

t_env	*envp_to_list(char **envp);
bool	add_env_node(t_env *env, char *str, int i);
char	**list_to_envp(t_env *env);
int		get_node_count(t_env *env);
void	free_env(t_env *env);
void	free_all_env(t_env *env);
bool	change_env_values(t_env *env, char **key_values);
bool	validation_env_key(char *key);

#endif
