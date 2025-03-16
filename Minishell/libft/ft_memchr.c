/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:11:05 by cfakoube          #+#    #+#             */
/*   Updated: 2024/05/27 14:57:03 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*ptr;
	char		uc;

	ptr = (const char *)s;
	uc = (char)c;
	while (n--)
	{
		if (*ptr == uc)
			return ((void *)ptr);
		ptr++;
	}
	return (0);
}
