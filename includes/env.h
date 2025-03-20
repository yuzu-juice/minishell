/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:25:30 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/19 15:19:36 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_value
{
	char			*value;
	struct s_value	*next;
}	t_value;

typedef struct s_env
{
	char			*key;
	t_value			*values;
	struct s_env	*next;
}	t_env;

t_env	*envp_to_list(char **envp);
void	add_env_node(t_env *env, char *str, int i);
char	**list_to_envp(t_env *env);
int 	get_node_count(t_env *env);
char	*create_values_str(t_value *values);

#endif
