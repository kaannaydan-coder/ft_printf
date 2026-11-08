/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaydan <kaydan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 15:01:28 by kaydan            #+#    #+#             */
/*   Updated: 2026/11/08 12:24:16 by kaydan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_ptr(unsigned long n)
{
	int	count;
	int	temp;

	count = 0;
	if (n == 0)
	{
		temp = ft_print_str("(nil)");
		if (temp == -1)
			return (-1);
		return (temp);
	}
	temp = ft_print_str("0x");
	if (temp == -1)
		return (-1);
	count += temp;
	temp = ft_print_hex2(n);
	if (temp == -1)
		return (-1);
	return (count + temp);
}

int	ft_print_hex2(unsigned long n)
{
	int	count;
	int	temp;
	int	rem;

	count = 0;
	if (n >= 16)
	{
		temp = ft_print_hex2(n / 16);
		if (temp == -1)
			return (-1);
		count += temp;
	}
	rem = n % 16;
	if (rem <= 9)
		temp = ft_print_char(rem + '0');
	else
		temp = ft_print_char(rem - 10 + 'a');
	if (temp == -1)
		return (-1);
	return (count + temp);
}
