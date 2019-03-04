/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 16:10:06 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/03 16:32:46 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_sprintf(const char *format, ...)
{
	char		*s;
	va_list		av;

	va_start(av, format);
	s = vaprintf(format, av);
	va_end(av);
	return (s);
}

int		ft_printf(const char *format, ...)
{
	int			l;
	char		*s;
	va_list		av;

	va_start(av, format);
	s = vaprintf(format, av);
	va_end(av);
	l = 0;
	while (s[l])
		l++;
	write(1, s, l);
	free(s);
	return (l);
}
