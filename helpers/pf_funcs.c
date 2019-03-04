/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_funcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:45:31 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/03 16:58:22 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vaprintf.h"

int		filler(char c, int l)
{
	int		i;
	char	*s;

	s = malloc(sizeof(char) * (l + 1));
	if (s == NULL)
		return (-1);
	s[l] = '\0';
	i = 0;
	while (i < l)
	{
		s[i] = c;
		i += 1;
	}
	write_str(s);
	free(s);
	return (0);
}

void	int_wrapper(va_list av, unsigned long flags, char type)
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
