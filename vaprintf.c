/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vaprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:26:32 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/03 18:31:03 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vaprintf.h"

char	*g_output;

static void	parse(int type, char **format, unsigned long flags, va_list av)
{
	char	c;

	c = **format;
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
		int_wrapper(av, flags, c);
	else if (type == 6)
		write_float(c, (flags & 2048) ?
			va_arg(av, long double) : va_arg(av, double), flags);
	else if (type == 7)
		render_format(format);
}

char		*vaprintf(const char *format, va_list av)
{
	int				type;
	unsigned long	flags;

	g_output = malloc(sizeof(char));
	g_output[0] = '\0';
	while (*format)
	{
		if (*format == '%')
		{
			flags = 0;
			type = resolve((char **)&format, &flags);
			parse(type, (char **)&format, flags, av);
		}
		else
			write_str_n(format, 1);
		format++;
	}
	return (g_output);
}
