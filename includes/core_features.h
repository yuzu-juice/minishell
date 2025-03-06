/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_features.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:31:13 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/02 19:07:59 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_FEATURES_H
# define CORE_FEATURES_H

void	exec_cmd(char **envp, char *str);

// from envp
char	*get_env_pwd(void);
char	**get_env_path(void);

// create cmd
char	*create_cmd_path(char *cmd);

#endif
