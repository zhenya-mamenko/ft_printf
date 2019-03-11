/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vaprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:26:32 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/10 18:06:47 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vaprintf.h"

char		*g_output;
int			g_outlen;

static void	print_np(char c, va_list av)
{
	char	cc;

	cc = (c == 'r') ? (char)va_arg(av, int) : 0;
	non_printable(c == 'r' ? &cc : va_arg(av, char *),
		c == 'r' ? 1 : 0);
}

static void	parse(int type, char **f, unsigned long fl, va_list av)
{
	char	cc;
	char	*s;

	if (type == 1)
		write_flags_str("%", 0, fl & ~32, **f);
	else if (type == 2)
		write_flags_str((s = va_arg(av, char *)) == NULL ? "(null)" : s,
			(fl & (255LL << 48)) ? (fl & (255LL << 48)) >> 48 : 0, fl, **f);
	else if (type == 3)
	{
		cc = (char)va_arg(av, int);
		write_flags_str(&cc, 1, fl, **f);
	}
	else if (type == 4)
		write_ull('x', (unsigned long)va_arg(av, void *), fl | 4096);
	else if (type == 5)
		int_wrapper(av, fl, **f);
	else if (type == 6)
		write_float(**f, (fl & 2048) ?
			va_arg(av, long double) : va_arg(av, double), fl);
	else if (type == 7)
		render_format(f);
	else if (type == 8)
		print_np(**f, av);
}

int			vaprintf(char **s, const char *format, va_list av)
{
	int				type;
	unsigned long	flags;

	g_output = malloc(sizeof(char) * BUFFSIZE);
	g_outlen = 0;
	while (*format)
	{
		if (*format == '%')
		{
			flags = 0;
			type = resolve((char **)&format, &flags);
			if (type != -1)
				parse(type, (char **)&format, flags, av);
			else if (*format != '\0')
				write_str_n(format, 1);
			else
				break ;
		}
		else
			write_str_n(format, 1);
		format++;
	}
	*s = g_output;
	return (g_outlen);
}
