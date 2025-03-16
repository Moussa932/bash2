/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:25:38 by cfakoube          #+#    #+#             */
/*   Updated: 2024/10/25 00:26:15 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*i;
	char	uc;

	i = (char *)s;
	uc = (char)c;
	if (uc == 0)
		return (&i[ft_strlen(i)]);
	while (*i)
	{
		if (*i == uc)
			return ((char *)i);
		else
			i++;
	}
	return (0);
}
