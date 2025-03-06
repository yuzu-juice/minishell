/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:58:26 by yohatana          #+#    #+#             */
/*   Updated: 2024/05/14 19:43:34 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	get_digit(long n);
static char	*put_int(char *result, long n, int digit, int minus_flg);

char	*ft_itoa(int n)
{
	char	*result;
	int		digit;
	int		minus_flg;
	long	temp;

	minus_flg = 1;
	if (n < 0)
		minus_flg = -1;
	temp = (long)n * minus_flg;
	digit = get_digit(temp);
	if (minus_flg == -1)
		digit++;
	result = (char *)malloc(digit + 1);
	if (result == 0)
		return (0);
	result = put_int(result, temp, digit, minus_flg);
	return (result);
}

static int	get_digit(long n)
{
	int	digit;

	digit = 0;
	if (n == 0)
		digit++;
	while (n > 0)
	{
		n = n / 10;
		digit++;
	}
	return (digit);
}

static char	*put_int(char *result, long n, int digit, int minus_flg)
{
	int	i;
	int	temp;

	i = digit;
	temp = 0;
	result[i] = '\0';
	i--;
	while (0 <= i)
	{
		if (minus_flg == -1 && i == 0)
			result[i] = '-';
		else
		{
			temp = n % 10;
			result[i] = temp + '0';
			n = n / 10;
		}
		i--;
	}
	return (result);
}
