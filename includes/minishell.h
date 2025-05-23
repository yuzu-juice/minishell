/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:27:24 by takitaga          #+#    #+#             */
/*   Updated: 2025/04/22 12:10:40 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "core_features.h"
# include "utils.h"
# include "signal_handlings.h"
# include "builtin_commands.h"
# include "env.h"
# include "redirections.h"
# include "pipes.h"
# include "exec.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <assert.h>
# include <string.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h>

extern volatile sig_atomic_t	g_sig_flag;

typedef struct s_minishell
{
	int		prev_status;
	t_env	*env;
	t_proc	*proc;
	int		proc_count;
	pid_t	*child_pids;
	int		created_child_proc_count;
}	t_minishell;

t_minishell	*create_minishell_struct(t_env *env);
void		free_minishell_struct(t_minishell *m_shell);
char		*get_input_line(void);

#endif
