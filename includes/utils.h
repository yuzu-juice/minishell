/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:57:03 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/22 19:45:24 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	free_string_double_array(char **str);
char	*add_slash(char *path);
char	*remove_quotes(char *token);
void	print_msg(char *str);
t_env	*serch_env(char *key, t_env *env);

#endif
