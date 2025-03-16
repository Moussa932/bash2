/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_putnbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:59:01 by cfakoube          #+#    #+#             */
/*   Updated: 2024/07/20 22:50:10 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_putnbr(long nb)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		nb = -nb;
		printf_putchar('-');
		i++;
	}
	if (nb > 9)
		i += printf_putnbr(nb / 10);
	printf_putchar(nb % 10 + '0');
	i++;
	return (i);
}
