/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:25:36 by cfakoube          #+#    #+#             */
/*   Updated: 2024/07/20 22:49:59 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	printf_strlen(char *str);
int	printf_putstr(char *str);
int	printf_putchar(char c);
int	printf_convertbasex(unsigned long n, char c);
int	printf_putadress(void *ptr);
int	printf_putnbr(long nb);
int	ft_printf(const char *str, ...);

#endif