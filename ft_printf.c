/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsasse <lsasse@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:05:17 by lsasse            #+#    #+#             */
/*   Updated: 2024/01/01 21:40:20 by lsasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putformat(const char **format, va_list ap)
{
	int	count;

	count = 0;
	++*format;
	if (**format == 'c')
		count = ft_putchar((char)va_arg(ap, int));
	else if (**format == 's')
		count = ft_putstr((char *)va_arg(ap, char *));
	else if (**format == 'i' || **format == 'd')
		count = ft_putnbr((int)va_arg(ap, int));
	else if (**format == 'u')
		count = ft_putunbr((long long unsigned int)va_arg(ap, unsigned int));
	else if (**format == 'x')
		count = ft_puthex((long long unsigned int)va_arg(ap, unsigned int), 0);
	else if (**format == 'X')
		count = ft_puthex((long long unsigned int)va_arg(ap, unsigned int), 1);
	else if (**format == 'p')
		count = ft_putptr((void *)va_arg(ap, void *));
	else if (**format == '%')
		count = ft_putchar('%');
	++*format;
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	ap;

	count = 0;
	if (!format)
		return (-1);
	va_start(ap, format);
	while (*format)
	{
		if (*format != '%')
			count += ft_putchar(*format++);
		else
			count += ft_putformat(&format, ap);
	}
	va_end(ap);
	return (count);
}
