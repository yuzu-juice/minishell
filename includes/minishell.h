/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:27:24 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/27 20:27:37 by takitaga         ###   ########.fr       */
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

#endif
