/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:25:30 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/20 14:40:03 by takitaga         ###   ########.fr       */
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
void	add_env_node(t_env *env, char *str, int i);
char	**list_to_envp(t_env *env);
int		get_node_count(t_env *env);

#endif
