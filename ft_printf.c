/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaydan <kaydan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 20:53:34 by kaydan            #+#    #+#             */
/*   Updated: 2026/10/20 23:21:18 by kaydan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
va_list	args; 
int		count;
int		i;

i = 0;
count = 0;
va_start (args, format);
while (format[i] != '\0')
{
	if (format[i] == '%')
	{	
		i++;
		if (format[i] == 'c')
			count += ft_print_char(va_arg(args, int));
		else if (format[i] == 's')
			count += ft_print_str(va_arg(args, char *));
		else if (format[i] == 'd' || format[i] == 'i')
			count += ft_print_nbr(va_arg(args, int));
		else if (format[i] == '%')
			count += ft_print_char('%');
		else if (format[i] == 'u')
			count += ft_print_unbr(va_arg(args, unsigned int));
		else if (format[i] == 'x' || format[i] == 'X')
			count += ft_print_hex(va_arg(args, unsigned int), format[i]);
		else if (format[i] == 'p')
			count += ft_print_ptr(va_arg(args, unsigned long));
		i++;
	}
	else
	{
		count += write(1, &format[i], 1);
		i++;
	}
}
va_end(args);
return (count);
}

int	ft_print_char(int c)
{
	char	letter;
	
	letter = c;
	write(1, &letter, 1);
	return (1);
}

int	ft_print_str(char *str)
{
	int	j;

	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	j = 0;
	while (str[j] != '\0')
	{
		write(1, &str[j], 1);
		j++;
	}
	return (j);
}

int	ft_print_nbr(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
		return (ft_print_str("-2147483648"));
	else if (n < 0)
	{
		count += ft_print_char('-');
		n *= -1;
	}
	if (n > 9)
		count += ft_print_nbr(n / 10);
	count += ft_print_char((n % 10) + '0');
	return (count);
}

int ft_print_unbr(unsigned int n)
{
	int	count;

	count = 0;
	if (n > 9)
		count += ft_print_unbr(n / 10);
	count += ft_print_char((n % 10) + '0');
	return (count);
}

int	ft_print_hex(unsigned int n, char format)
{
	int	count;
	int	rem;

	count = 0;
	if (n >= 16)
		count += ft_print_hex((n / 16), format);
	rem = n % 16;
	if (rem <= 9)
		count += ft_print_char(rem + '0');
	else
	{
		if (format == 'x')
			count += ft_print_char(rem - 10 + 'a');
		else if (format == 'X')
			count += ft_print_char(rem - 10 + 'A');
	}
	return (count);
}

int	ft_print_ptr(unsigned long n)
{
	int	count;

	count = 0;
	if (n == 0)
	{
		count += ft_print_str("0x0");
		return (count);
	}
	count += ft_print_str("0x");
	count += ft_print_hex2(n);
	return (count);
}

int	ft_print_hex2(unsigned long n)
{
	int	count;
	int	rem;

	count = 0;
	if (n >= 16)
		count += ft_print_hex2(n / 16);
	rem = n % 16;
	if (rem <= 9)
		count += ft_print_char(rem + '0');
	else
		count += ft_print_char(rem - 10 + 'a');
	return (count);
}
