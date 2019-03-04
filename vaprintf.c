/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vaprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:26:32 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/03 16:19:46 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vaprintf.h"

char					*g_output;

static unsigned long	resolve_flags(char **s)
{
	unsigned long	result;
	unsigned long	l;

	result = 0;
	if ((*s)[1] == '#')
	{
		result |= 16;
		(*s) += 1;
	}
	if ((*s)[1] == ' ')
	{
		result |= 128;
		(*s) += 1;
	}
	if ((*s)[1] == '-')
	{
		result |= 512;
		(*s) += 1;
	}
	if ((*s)[1] == '+')
	{
		result = (result & ~128) | 256;
		(*s) += 1;
	}
	if ((*s)[1] == '0')
	{
		result |= (result & 512 ? 0 : 64);
		(*s) += 1;
	}
	if ((*s)[1] >= '1' && (*s)[1] <= '9')
	{
		*s += 1;
		l = atoi_s(s);
		result |= 1024 | (l << 56);
	}
	if ((*s)[1] == '.')
	{
		*s += 2;
		l = atoi_s(s);
		result = (result & ~64) | 32 | (l << 48);
	}
	return (result);
}

static unsigned long	resolve_len_flags(char **s)
{
	long	result;

	result = 0;
	if ((*s)[1] == 'h')
		result |= 1 | ((*s)[2] == 'h' ? 2 : 0);
	else if ((*s)[1] == 'l')
		result |= 4 | ((*s)[2] == 'l' ? 8 : 0);
	else if ((*s)[1] == 'L')
		result |= 2048;
	*s += 1 + ((*s)[2] == 'h' || (*s)[2] == 'l' ? 1 : 0);
	return (result);
}

static int				resolve(char **s, unsigned long *flags)
{
	int	result;

	result = 0;
	if ((*s)[1] == '#' || (*s)[1] == '0' || (*s)[1] == '-' || (*s)[1] == '+' ||
		(*s)[1] == ' ' || (*s)[1] == '.' || ((*s)[1] >= '0' && (*s)[1] <= '9'))
		*flags += resolve_flags(s);
	if ((*s)[1] == 'l' || (*s)[1] == 'L' || (*s)[1] == 'h')
		*flags += resolve_len_flags(s);
	if ((*s)[1] == '%')
		result = 1;
	else if ((*s)[1] == 's')
		result = 2;
	else if ((*s)[1] == 'c')
		result = 3;
	else if ((*s)[1] == 'p')
		result = 4;
	else if ((*s)[1] == 'd' || (*s)[1] == 'i' || (*s)[1] == 'o' ||
		(*s)[1] == 'u' || (*s)[1] == 'x' || (*s)[1] == 'X' || (*s)[1] == 'b')
		result = 5;
	else if ((*s)[1] == 'f')
		result = 6;
	else if ((*s)[1] == '~')
		result = 7;
	*s += 1;
	return (result);
}

static void				wrap(va_list av, unsigned long flags, char type)
{
	int		stub;
	int		sign;

	sign = (type == 'd' || type == 'i') ? 1 : 0;
	if (flags & 1)
		stub = sign == 1 ? write_ll(type, (short)va_arg(av, int), flags) :
			write_ull(type, (unsigned short)va_arg(av, unsigned int), flags);
	else if (flags & 2)
		stub = sign == 1 ? write_ll(type, (char)va_arg(av, int), flags) :
			write_ull(type, (unsigned char)va_arg(av, unsigned int), flags);
	else if (flags & 4)
		stub = sign == 1 ? write_ll(type, va_arg(av, long), flags) :
			write_ull(type, va_arg(av, unsigned long), flags);
	else if (flags & 8)
		stub = sign == 1 ? write_ll(type, va_arg(av, long long), flags) :
			write_ull(type, va_arg(av, unsigned long long), flags);
	else
		stub = sign == 1 ? write_ll(type, va_arg(av, int), flags) :
			write_ull(type, va_arg(av, unsigned int), flags);
}

char					*vaprintf(const char *format, va_list av)
{
	int				type;
	char			c;
	unsigned long	flags;

	g_output = malloc(sizeof(char));
	g_output[0] = '\0';
	while (*format)
	{
		if (*format == '%')
		{
			flags = 0;
			type = resolve((char **)&format, &flags);
			c = *format;
			if (type == 1)
				write_str("%");
			else if (type == 2)
				write_flags_str(va_arg(av, char *), (flags & (255LL << 48)) ?
					(flags & (255LL << 48)) >> 48 : 0, flags, c);
			else if (type == 3)
			{
				c = (char)va_arg(av, int);
				write_str_n(&c, 1);
			}
			else if (type == 4)
				write_ull('x', (unsigned long)va_arg(av, void *), 16);
			else if (type == 5)
				wrap(av, flags, c);
			else if (type == 6)
			{
				if (flags & 2048)
					write_float(c, va_arg(av, long double), flags);
				else
					write_float(c, va_arg(av, double), flags);
			}
			else if (type == 7)
				render_format((char **)&format);
		}
		else
			write_str_n(format, 1);
		format++;
	}
	return (g_output);
}
