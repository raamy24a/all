/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:56:30 by radib             #+#    #+#             */
/*   Updated: 2025/05/05 16:14:08 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <unistd.h>

static int	ten_pow(int pow)
{
	int	i;

	i = 1;
	while (pow - 1 > 0)
	{
		i *= 10;
		pow--;
	}
	return (i);
}

static int	nbr_len(int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_put_unsinged(unsigned int decimal)
{
	unsigned int	n;
	int				i;
	int				c;

	n = decimal;
	if (n == 0)
		write(1, "0", 1);
	i = nbr_len(n);
	while (i > 0)
	{
		c = (n / ten_pow(i)) + 48;
		n = n % ten_pow(i);
		write(1, &c, 1);
		i--;
	}
	n = decimal;
	return (nbr_len(n));
}

int	ft_putnbr(int n)
{
	char	c;
	int		i;
	int		l;

	l = n;
	if (n < 0)
	{
		n *= -1;
		write(1, "-", 1);
	}
	if (n == 0)
		write(1, "0", 1);
	if (n == -2147483648)
		write(1, "2147483648", 10);
	i = nbr_len(n);
	while (i > 0)
	{
		c = (n / ten_pow(i)) + 48;
		n = n % ten_pow(i);
		write(1, &c, 1);
		i--;
	}
	return (nbr_len(l));
}