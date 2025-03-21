/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:11:36 by yohatana          #+#    #+#             */
/*   Updated: 2025/03/20 14:54:36 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char			**create_cmd_args(char *cmd);
static t_builtin	resolve_builtin_cmd(char *cmd);
static void			exec_builtin(char **cmd_args, t_builtin cmd, t_env *envp);

void	exec_cmd(t_env *env, char *cmd)
{
	char		*cmd_path;
	char		**cmd_args;
	t_builtin	builtin_cmd;
	int			i;

	i = 0;
	cmd_args = create_cmd_args(cmd);
	if (cmd_args == NULL)
		perror(NULL);
	while (cmd_args[i] != NULL)
	{
		cmd_args[i] = remove_quotes(cmd_args[i]);
		i++;
	}
	builtin_cmd = resolve_builtin_cmd(cmd_args[0]);
	if (builtin_cmd != NOT_A_BUILTIN_COMMAND)
		exec_builtin(cmd_args, builtin_cmd, env);
	cmd_path = create_cmd_path(cmd);
	if (cmd_path == NULL)
		perror(NULL);
	if (execve(cmd_path, cmd_args, list_to_envp(env)) == -1)
		perror(NULL);
}

static char	**create_cmd_args(char *cmd)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd, ' ');
	return (cmd_args);
}

// TODO: replace ft_strncmp to ft_strcmp
static t_builtin	resolve_builtin_cmd(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (ECHO);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (PWD);
	return (NOT_A_BUILTIN_COMMAND);
}

static void	exec_builtin(char **cmd_args, t_builtin builtin_cmd, t_env *env)
{
	int	i;

	(void)env;
	i = 0;
	while (cmd_args[i] != NULL)
		i++;
	if (builtin_cmd == ECHO)
		echo(i, cmd_args);
	else if (builtin_cmd == PWD)
		pwd(i);
	free_string_double_array(cmd_args);
	exit(EXIT_SUCCESS);
}
