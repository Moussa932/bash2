/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:42:35 by cfakoube          #+#    #+#             */
/*   Updated: 2024/07/20 22:51:09 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static void	ft_putstr(char **strs, char const *str, char c, size_t words)
{
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	end;

	start = 0;
	j = 0;
	while (str[start] && j < words)
	{
		while (str[start] && str[start] == c)
			start++;
		end = start;
		while (str[end] && str[end] != c)
			end++;
		strs[j] = malloc(sizeof(char) * (end - start + 1));
		if (strs[j] == NULL)
			return (ft_freetab(strs));
		i = 0;
		while (start < end)
			strs[j][i++] = str[start++];
		strs[j++][i] = '\0';
	}
	strs[j] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	words;

	words = ft_count_words(s, c);
	strs = malloc(sizeof(char *) * (words + 1));
	if (strs == NULL)
		return (NULL);
	ft_putstr(strs, s, c, words);
	return (strs);
}
