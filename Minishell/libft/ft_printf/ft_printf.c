/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:24:23 by cfakoube          #+#    #+#             */
/*   Updated: 2024/07/20 22:49:54 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	printf_convert(va_list args, char c)
{
	va_list	args_copy;

	va_copy(args_copy, args);
	if (c == 'c')
		return (printf_putchar(va_arg(args, int)));
	else if (c == 's')
	{
		if (va_arg(args, char *) == NULL)
			return (printf_putstr("(null)"));
		return (printf_putstr(va_arg(args_copy, char *)));
	}
	else if (c == 'p')
		return (printf_putadress(va_arg(args, void *)));
	else if (c == 'd' || c == 'i')
		return (printf_putnbr(va_arg(args, int)));
	else if (c == 'u')
		return (printf_putnbr(va_arg(args, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (printf_convertbasex(va_arg(args, unsigned int), c));
	else if (c == '%')
		return (printf_putchar('%'));
	else
		return (0);
}

static int	printf_isconvertible(char c)
{
	int		i;
	char	*str;

	i = 0;
	str = "cspdiuxX%";
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		slen;
	va_list	args;

	i = 0;
	slen = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && printf_isconvertible(str[i + 1]))
		{
			slen += printf_convert(args, str[i + 1]);
			i++;
		}
		else
			slen += printf_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (slen);
}
/*
int	main(void)
{
	printf("%i\n", printf("ca va pas gerer les erreurs\n"));
	ft_printf("%i\n", ft_printf("ca va pas gerer les erreurs\n"));
}*/