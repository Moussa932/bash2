/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:42:18 by cfakoube          #+#    #+#             */
/*   Updated: 2024/05/28 15:49:22 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_numlen(int n)
{
	int	i;
	int	nb;

	i = 0;
	nb = n;
	if (n == -2147483648)
		return (11);
	while (nb)
	{
		nb /= 10;
		i++;
	}
	if (n <= 0)
		i++;
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	i = ft_numlen(n);
	str = malloc(sizeof(char) * (i + 1));
	if (str == 0)
		return (0);
	str[i] = '\0';
	if (n < 0)
		str[0] = '-';
	if (n == 0)
		str[0] = '0';
	while (n)
	{
		if (n < 0)
			str[--i] = '0' - (n % 10);
		else
			str[--i] = '0' + (n % 10);
		n /= 10;
	}
	return (str);
}
