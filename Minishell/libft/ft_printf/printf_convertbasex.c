/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_convertbasex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:56:48 by cfakoube          #+#    #+#             */
/*   Updated: 2024/07/20 22:50:02 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_convertbasex(unsigned long n, char c)
{
	int		i;
	char	*base;

	i = 0;
	if (c == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n > 15)
		i += printf_convertbasex(n / 16, c);
	printf_putchar(base[n % 16]);
	i++;
	return (i);
}
