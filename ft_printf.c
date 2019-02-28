/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:26:32 by emamenko          #+#    #+#             */
/*   Updated: 2019/02/27 17:48:34 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	resolve_flags(const char **s)
{
	int		result;
	char	c;

	result = 0;
	c = (*s)[1];
	if (c == 'h')
		result = 1 + ((*s)[2] == 'h' ? 2 : 0);
	else if (c == 'l')
		result = 4 + ((*s)[2] == 'l' ? 8 : 0);
	*s += 1 + ((*s)[2] == 'h' || (*s)[2] == 'l' ? 1 : 0);
	return (result);
}

static int	resolve(const char **s, int *flags)
{
	int		result;
	char	c;

	result = 0;
	c = (*s)[1];
	if (c == 'l' || c == 'L' || c == 'h' || c == '#' || c == '0' || c == '-' ||
		c == '+' || c == ' ' || c == '.' || (c >= '0' && c <= '9'))
		*flags = resolve_flags(s);
	c = (*s)[1];
	if (c == '%')
		result = 1;
	else if (c == 's')
		result = 2;
	else if (c == 'c')
		result = 3;
	else if (c == 'p')
		result = 4;
	else if (c == 'd' || c == 'i' || c == 'o' || c == 'u'
		|| c == 'x' || c == 'X' || c == 'y' || c == 'Y' || c == 'b')
		result = 5;
	*s += 1;
	return (result);
}

static void	wrap(va_list av, int flags, char type)
{
	int		stub;
	int		sign;

	sign = (type == 'd' || type == 'i') ? 1 : 0;
	if (flags == 0)
		stub = sign == 1 ? write_ll(type, va_arg(av, int)) :
			write_ull(type, va_arg(av, unsigned int));
	else if (flags == 1)
		stub = sign == 1 ? write_ll(type, (short)va_arg(av, int)) :
			write_ull(type, (unsigned short)va_arg(av, unsigned int));
	else if (flags == 3)
		stub = sign == 1 ? write_ll(type, (char)va_arg(av, int)) :
			write_ull(type, (unsigned char)va_arg(av, unsigned int));
	else if (flags == 4)
		stub = sign == 1 ? write_ll(type, va_arg(av, long)) :
			write_ull(type, va_arg(av, unsigned long));
	else if (flags == 12)
		stub = sign == 1 ? write_ll(type, va_arg(av, long long)) :
			write_ull(type, va_arg(av, unsigned long long));
}

int			ft_printf(const char *format, ...)
{
	va_list		av;
	int			type;
	char		c;
	int			flags;

	va_start(av, format);
	while (*format)
	{
		if (*format == '%')
		{
			flags = 0;
			type = resolve(&format, &flags);
			c = *format;
			if (type == 1)
				write_str("%");
			else if (type == 2)
				write_str(va_arg(av, char *));
			else if (type == 3)
			{
				c = (char)va_arg(av, int);
				write(1, &c, 1);
			}
			else if (type == 4)
				write_ull('y', (unsigned long)va_arg(av, void *));
			else if (type == 5)
				wrap(av, flags, c);
		}
		else
			write(1, format, 1);
		format++;
	}
	va_end(av);
	return (0);
}
