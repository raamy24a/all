/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:29:15 by radib             #+#    #+#             */
/*   Updated: 2025/05/06 14:57:16 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <unistd.h>

int	ft_putstr(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (ft_putstr("(null)"));
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_hexa( unsigned int decimal, char x)
{
	unsigned long		temp;
	int					len;
	char				buffer[16];
	int					i;

	len = 0;
	if (!decimal)
		return (ft_putstr("0"));
	while (decimal > 0)
	{
		temp = decimal % 16;
		if ((temp >= 10 && x == 'x'))
			temp += 39;
		else if (temp >= 10 && x == 'X')
			temp += 7;
		buffer[len] = temp + '0';
		decimal /= 16;
		len++;
	}
	i = len;
	while (i--)
		write(1, &buffer[i], 1);
	return (len);
}

int	ft_hexa_void( unsigned long decimal)
{
	unsigned long		temp;
	int					len;
	char				buffer[16];
	int					i;

	len = 0;
	if (!decimal)
		return (ft_putstr("(nil)"));
	while (decimal > 0)
	{
		temp = decimal % 16;
		if (temp >= 10)
			temp += 39;
		buffer[len] = temp + '0';
		decimal /= 16;
		len++;
	}
	i = len;
	len += ft_putstr("0x");
	while (i--)
		write(1, &buffer[i], 1);
	return (len);
}

int	ft_convert(va_list args, char format_str)
{
	unsigned long	len;
	char			c;

	len = 1;
	if (format_str == 'c')
	{
		c = va_arg(args, int);
		write(1, &c, 1);
	}
	else if (format_str == 's')
		len = ft_putstr(va_arg(args, char *));
	else if (format_str == 'p')
	{
		len = (unsigned long)va_arg(args, void *);
		len = ft_hexa_void(len);
	}
	else if (format_str == 'd' || format_str == 'i')
		len = ft_putnbr(va_arg(args, int));
	else if (format_str == 'u')
		len = ft_put_unsigned(va_arg(args, unsigned int));
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
	char			temp;

	len = 0;
	va_start(args, format_str);
	while (*format_str)
	{
		if (*format_str == '%')
		{
			format_str++;
			len += ft_convert(args, *format_str);
			format_str++;
		}
		else
		{
			len++;
			temp = *format_str;
			write(1, &temp, 1);
			format_str++;
		}
	}
	va_end(args);
	return (len);
}
// int	main(void)
// {
// printf("%x\n", 0);
// ft_printf("%x\n", 0);
// }