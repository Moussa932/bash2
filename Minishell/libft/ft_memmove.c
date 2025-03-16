/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:59:52 by cfakoube          #+#    #+#             */
/*   Updated: 2024/05/27 09:04:39 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s1;
	char	*s2;
	size_t	i;

	s1 = (char *)src;
	s2 = (char *)dest;
	i = 0;
	if (dest == 0 && src == 0)
		return (0);
	if (s2 > s1)
	{
		while (n-- > 0)
			s2[n] = s1[n];
	}
	else
	{
		while (i < n)
		{
			s2[i] = s1[i];
			i++;
		}
	}
	return (dest);
}
