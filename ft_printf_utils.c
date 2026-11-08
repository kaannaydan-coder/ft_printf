/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaydan <kaydan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 14:30:09 by kaydan            #+#    #+#             */
/*   Updated: 2026/11/08 12:12:51 by kaydan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int c)
{
	char	letter;

	letter = c;
	if (write(1, &letter, 1) == -1)
		return (-1);
	return (1);
}

int	ft_print_str(char *str)
{
	int	j;

	if (!str)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	j = 0;
	while (str[j] != '\0')
	{
		if (write(1, &str[j], 1) == -1)
			return (-1);
		j++;
	}
	return (j);
}

int	ft_print_nbr(int n)
{
	int	count;
	int	temp;

	count = 0;
	if (n == -2147483648)
		return (ft_print_str("-2147483648"));
	if (n < 0)
	{
		temp = ft_print_char('-');
		if (temp == -1)
			return (-1);
		count += temp;
		n *= -1;
	}
	if (n > 9)
	{
		temp = ft_print_nbr(n / 10);
		if (temp == -1)
			return (-1);
		count += temp;
	}
	temp = ft_print_char((n % 10) + '0');
	if (temp == -1)
		return (-1);
	return (count + temp);
}

int	ft_print_unbr(unsigned int n)
{
	int	count;
	int	temp;

	count = 0;
	if (n > 9)
	{
		temp = ft_print_unbr(n / 10);
		if (temp == -1)
			return (-1);
		count += temp;
	}
	temp = ft_print_char((n % 10) + '0');
	if (temp == -1)
		return (-1);
	return (count + temp);
}

int	ft_print_hex(unsigned int n, char format)
{
	int	count;
	int	temp;
	int	rem;

	count = 0;
	if (n >= 16)
	{
		temp = ft_print_hex((n / 16), format);
		if (temp == -1)
			return (-1);
		count += temp;
	}
	rem = n % 16;
	if (rem <= 9)
		temp = ft_print_char(rem + '0');
	else if (format == 'x')
		temp = ft_print_char(rem - 10 + 'a');
	else
		temp = ft_print_char(rem - 10 + 'A');
	if (temp == -1)
		return (-1);
	return (count + temp);
}
