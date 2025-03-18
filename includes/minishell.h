/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:27:24 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/18 16:04:04 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "core_features.h"
# include "utils.h"
# include "signal_handlings.h"

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

extern volatile sig_atomic_t	g_sig_flag;

#endif
