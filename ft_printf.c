/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaydan <kaydan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 20:53:34 by kaydan            #+#    #+#             */
/*   Updated: 2026/11/07 15:51:51 by kaydan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_format(char type, va_list *args)
{
	int	count;

	count = 0;
	if (type == 'c')
		count += ft_print_char(va_arg(*args, int));
	else if (type == 's')
		count += ft_print_str(va_arg(*args, char *));
	else if (type == 'd' || type == 'i')
		count += ft_print_nbr(va_arg(*args, int));
	else if (type == '%')
		count += ft_print_char('%');
	else if (type == 'u')
		count += ft_print_unbr(va_arg(*args, unsigned int));
	else if (type == 'x' || type == 'X')
		count += ft_print_hex(va_arg(*args, unsigned int), type);
	else if (type == 'p')
		count += ft_print_ptr(va_arg(*args, unsigned long));
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		temp;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
			temp = ft_check_format(*(++format), &args);
		else
			temp = write(1, format, 1);
		if (temp == -1 || !*format)
			break ;
		count += temp;
		format++;
	}
	va_end(args);
	if (temp == -1)
		return (-1);
	return (count);
}
