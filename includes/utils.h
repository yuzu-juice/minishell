/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:57:03 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/20 15:31:05 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	free_string_double_array(char **str);
char	*add_slash(char *path);
char	*remove_quotes(char *token);
t_env	*search_env(char *key, t_env *env);
int		count_double_string_array(char **str);
bool	copy_double_string_array(char **src, char **new, char *word);

// debug
void	print_double_string_array(char **str);

#endif
