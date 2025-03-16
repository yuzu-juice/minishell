/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takitaga <takitaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:45:06 by takitaga          #+#    #+#             */
/*   Updated: 2025/03/16 11:31:46 by takitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    echo(int argc, char **argv)
{
    int  i;

    i = 1;
    if (argc == 1)
        write(1, "\n", 1);
    while (i < argc - 1)
    {
        write(1, argv[i], ft_strlen(argv[i]));
        i++;
    }
}

// int main(int argc, char **argv)
// {
//     echo(argc, argv);
//     return (0);
// }
