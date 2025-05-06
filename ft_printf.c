/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:29:15 by radib             #+#    #+#             */
/*   Updated: 2025/05/06 12:50:57 by radib            ###   ########.fr       */
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

int	ft_hexa( unsigned long decimal, char x)
{
	unsigned long		temp;
	int					len;
	char				buffer[16];
	int					i;

	len = 0;
	if (decimal == 0)
		return (ft_putstr("(nil)"));
	while (decimal > 0)
	{
		temp = decimal % 16;
		if (temp >= 10 && x == 'x' || temp >= 10 && x == 'p')
			temp += 39;
		else if (temp >= 10 && x == 'X')
			temp += 7;
		buffer[len] = temp + '0';
		decimal /= 16;
		len++;
	}
	i = len;
	if (x == 'p')
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
		len = ft_hexa(len, 'p');
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

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

// Declare your function prototype

int main(void)
{
    char c = 'A';
    char *s = "Hello, world!";
    char *null_s = NULL;
    void *ptr = &c;
    void *null_ptr = NULL;
    int d = -12345;
    int i = 67890;
    unsigned int u = 4294967295U;
    int x = 305441741; // 0x1234ABCD
    int X = 305441741;

    printf("========= %%c (char) =========\n");
    printf("printf:   [%d chars] '", printf("%c'\n", c));
    printf("ft_printf: [%d chars] '", ft_printf("%c'\n", c));

    printf("========= %%s (string) =========\n");
    printf("printf:   [%d chars] '", printf("%s'\n", s));
    printf("ft_printf: [%d chars] '", ft_printf("%s'\n", s));

    printf("========= %%s (NULL string) =========\n");
    printf("printf:   [%d chars] '", printf("%s'\n", null_s));
    printf("ft_printf: [%d chars] '", ft_printf("%s'\n", null_s));

    printf("========= %%p (pointer) =========\n");
    printf("printf:   [%d chars] '", printf("%p'\n", ptr));
    printf("ft_printf: [%d chars] '", ft_printf("%p'\n", ptr));

    printf("========= %%p (NULL pointer) =========\n");
    printf("printf:   [%d chars] '", printf("%p'\n", null_ptr));
    printf("ft_printf: [%d chars] '", ft_printf("%p'\n", null_ptr));

    printf("========= %%d (int, negative) =========\n");
    printf("printf:   [%d chars] '", printf("%d'\n", d));
    printf("ft_printf: [%d chars] '", ft_printf("%d'\n", d));

    printf("========= %%d (int, zero) =========\n");
    printf("printf:   [%d chars] '", printf("%d'\n", 0));
    printf("ft_printf: [%d chars] '", ft_printf("%d'\n", 0));

    printf("========= %%d (int, INT_MAX) =========\n");
    printf("printf:   [%d chars] '", printf("%d'\n", INT_MAX));
    printf("ft_printf: [%d chars] '", ft_printf("%d'\n", INT_MAX));

    printf("========= %%d (int, INT_MIN) =========\n");
    printf("printf:   [%d chars] '", printf("%d'\n", INT_MIN));
    printf("ft_printf: [%d chars] '", ft_printf("%d'\n", INT_MIN));

    printf("========= %%i (int, positive) =========\n");
    printf("printf:   [%d chars] '", printf("%i'\n", i));
    printf("ft_printf: [%d chars] '", ft_printf("%i'\n", i));

    printf("========= %%u (unsigned int) =========\n");
    printf("printf:   [%d chars] '", printf("%u'\n", u));
    printf("ft_printf: [%d chars] '", ft_printf("%u'\n", u));

    printf("========= %%x (hex, lowercase) =========\n");
    printf("printf:   [%d chars] '", printf("%x'\n", x));
    printf("ft_printf: [%d chars] '", ft_printf("%x'\n", x));

    printf("========= %%X (hex, uppercase) =========\n");
    printf("printf:   [%d chars] '", printf("%X'\n", X));
    printf("ft_printf: [%d chars] '", ft_printf("%X'\n", X));

    printf("========= %% (percent sign) =========\n");
    printf("printf:   [%d chars] '", printf("%%\n"));
    printf("ft_printf: [%d chars] '", ft_printf("%%\n"));

    printf("========= Combo test =========\n");
    printf("printf:   [%d chars] '", printf("Char: %c, String: %s, Pointer: %p, Dec: %d, Int: %i, Unsigned: %u, Hex: %x, HEX: %X, Percent: %%\n",
        c, s, ptr, d, i, u, x, X));
    printf("ft_printf: [%d chars] '", ft_printf("Char: %c, String: %s, Pointer: %p, Dec: %d, Int: %i, Unsigned: %u, Hex: %x, HEX: %X, Percent: %%\n",
        c, s, ptr, d, i, u, x, X));

    return 0;
}
