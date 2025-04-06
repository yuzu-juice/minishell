/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:23:12 by yohatana          #+#    #+#             */
/*   Updated: 2025/04/06 17:00:21 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# define PREV 0
# define CURR 1
# define READ 0
# define WRITE 1

typedef struct s_minishell	t_minishell;

bool	minishell_pipe(t_minishell *minishell);

#endif
