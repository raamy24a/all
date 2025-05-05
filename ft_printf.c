/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:29:15 by radib             #+#    #+#             */
/*   Updated: 2025/05/05 12:11:20 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

int	ft_hexa( int decimal, char x)
{
	int	temp;
	int	len;

	len = 0;
	while (decimal > 0)
	{
		temp = decimal % 16;
		if (temp < 10)
			write(1, &temp, 1);
		else if (x == 'x')
			write(1, &temp + 39, 1);
		else
			write(1, &temp + 7, 1);
		decimal /= 16;
		len++;
	}
	return (len);
}

int	ft_convert(va_list args, char format_str)
{
	int	len;

	len = 1;
	if (format_str == 'c')
		write(1, (va_arg(args, int)), 1);
	else if (format_str == 's')
		len = ft_putstr_fd(va_arg(args, char *));
	else if (format_str == 'p')
		len = ft_hexa_void(va_arg(args, char *));
	else if (format_str == 'd')
		len = ft_put_decimal(va_arg(args, char *));
	else if (format_str == 'i')
		len = ft_putnumber(va_arg(args, char *));
	else if (format_str == 'u')
		len = ft_put_unsinged_decimal(va_arg(args, char *));
	else if (format_str == 'X' || format_str == 'x')
		len = ft_hexa(va_arg(args, int), format_str);
	else if (format_str == '%')
		write (1, "%", 1);
	return (len);
}

int	ft_printf(const char *format_str, ...)
{
	unsigned int	len;
	va_list			args;

	len = 0;
	va_start(args, format_str);
	while (format_str)
	{
		if (format_str == '%')
			len += ft_convert(args, *format_str++);
		else
			len++ && write(1, format_str++, 1);
	}
	va_end(args);
	return (len);
}
