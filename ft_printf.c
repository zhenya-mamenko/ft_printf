/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:26:32 by emamenko          #+#    #+#             */
/*   Updated: 2019/02/27 11:48:41 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	resolve(const char *s, int *pos)
{
	*pos += 1;
	if (*s == '%')
		return (1);
	else if (*s == 's')
		return (2);
	else if (*s == 'c')
		return (3);
	else if (*s == 'p')
		return (4);
	else if (*s == 'd' || *s == 'i' || *s == 'o' || *s == 'u'
		|| *s == 'x' || *s == 'X' || *s == 'y' || *s == 'Y' || *s == 'b')
		return (5);
	return (0);
}

int			ft_printf(const char *format, ...)
{
	va_list		av;
	int			i;
	int			type;
	char		c;

	va_start(av, format);
	i = -1;
	while (format[++i])
		if (format[i] == '%')
		{
			type = resolve(format + i + 1, &i);
			c = format[i];
			if (type == 1)
				write_str("%");
			else if (type == 2)
			{
				write_str(va_arg(av, char *));
			}
			else if (type == 3)
			{
				c = (char)va_arg(av, int);
				write(1, &c, 1);
			}
			else if (type == 4)
				write_ull('y', (unsigned long)va_arg(av, void *));
			else if (type == 5)
			{
				if (c == 'd' || c == 'i')
					write_ll(c, va_arg(av, int));
				else
					write_ull(c, va_arg(av, unsigned int));
			}
		}
		else
			write(1, format + i, 1);
	va_end(av);
	return (0);
}
