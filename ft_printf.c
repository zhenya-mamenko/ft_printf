/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:26:32 by emamenko          #+#    #+#             */
/*   Updated: 2019/02/26 16:59:05 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	len(char *s)
{
	int		l;

	l = 0;
	while (s[l])
		l += 1;
	return (l);
}

static int	resolve(const char *s, int *pos)
{
	*pos += 1;
	if (*s == '%')
		return (1);
	else if (*s == 's')
		return (2);
	return (0);
}

int			ft_printf(const char *format, ...)
{
	va_list		av;
	char		*tra;
	int			i;
	int			type;

	va_start(av, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			type = resolve(format + i + 1, &i);
			if (type == 1)
				write(1, "%", 1);
			else if (type == 2)
			{
				tra = va_arg(av, char*);
				write(1, tra, len(tra));
			}
		}
		else
			write(1, format + i, 1);
		i += 1;
	}
	va_end(av);
	return (0);
}
