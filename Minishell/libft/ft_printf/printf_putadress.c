/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_putadress.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:57:53 by cfakoube          #+#    #+#             */
/*   Updated: 2024/07/20 22:50:05 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_putadress(void *ptr)
{
	int				i;
	unsigned long	n;

	if (ptr == NULL)
		return (printf_putstr("(nil)"));
	n = (unsigned long)ptr;
	i = printf_putstr("0x");
	i += printf_convertbasex(n, 'x');
	return (i);
}
