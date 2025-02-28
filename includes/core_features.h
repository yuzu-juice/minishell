/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_features.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:31:13 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/28 15:45:32 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_FEATURES_H
# define CORE_FEATURES_H

void	exec_cmd(char **envp, char *str);

// from envp
char	*get_env_pwd(char **envp);
char	**get_env_path(char **envp);

// create cmd
char	*create_cmd_path(char **envp, char *cmd);
// char	**create_cmd_args(char *cmd);

#endif
