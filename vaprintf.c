/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vaprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:26:32 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/03 17:01:27 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vaprintf.h"

char	*g_output;

char	*vaprintf(const char *format, va_list av)
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
				int_wrapper(av, flags, c);
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
