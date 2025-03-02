/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:22:19 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/25 14:17:59 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	count_word(char const *s, char c);
static void	result_free(char **result);
static int	word_split(char **result, char const *s, char sep, int count_w);
static char	*word_copy(int start, int count, char const *s);

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		count_w;
	int		answer;

	if (s == NULL)
		return (NULL);
	count_w = count_word(s, c);
	result = (char **)ft_calloc(sizeof(char *), (count_w + 1));
	if (result == NULL)
		return (NULL);
	answer = word_split(result, s, c, count_w);
	if (answer == 0)
		result_free(result);
	result[count_w] = NULL;
	return (result);
}

static int	count_word(char const *s, char c)
{
	int	count;
	int	char_flg;
	int	i;

	count = 0;
	i = 0;
	char_flg = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			char_flg = 0;
		else
		{
			if (char_flg == 0)
			{
				count++;
				char_flg = 1;
			}
		}
		i++;
	}
	return (count);
}

// return 0 is fail
static int	word_split(char **result, char const *s, char sep, int count_w)
{
	int		start;
	int		count;
	int		index;

	start = 0;
	index = 0;
	while (s[start] != '\0' && index < count_w)
	{
		if (s[start] != sep)
		{
			count = 0;
			while (s[start + count] != '\0' && s[start + count] != sep)
				count++;
			result[index] = word_copy(start, count, s);
			if (result[index] == NULL)
				return (0);
			start = start + count - 1;
			index++;
		}
		start++;
	}
	result[index] = NULL;
	return (1);
}

static char	*word_copy(int start, int count, char const *s)
{
	int		j;
	char	*word;

	word = (char *)ft_calloc(count + 1, 1);
	if (word == NULL)
		return (NULL);
	j = 0;
	while (j < count)
	{
		word[j] = s[start + j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

static void	result_free(char	**result)
{
	int	i;

	i = 0;
	while (result[i] != NULL)
	{
		free(result[i]);
		i++;
	}
	free(result);
}

// #include<stdio.h>
// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }
// int main()
// {
// 	char **test = ft_split("hello!", ' ');
// 	for(int i = 0;test[i] != NULL;i++)
// 	{
// 		printf("%s\n",test[i]);
// 	}
// 	for(int i = 0;test[i] != NULL;i++)
// 	{
// 		free(test[i]);
// 	}
// 	free(test);
// }
