/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:57:03 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/08 19:39:39 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	free_string_double_array(char **str);
char	*add_slash(char *path);
char	*remove_quotes(char *token);
t_env	*search_env(char *key, t_env *env);
char	**split_string(char *str, char delimiter);

#endif
