/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolvers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 16:59:55 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/03 23:40:01 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vaprintf.h"
#include "resolvers.h"

static int		check_and_set(unsigned long *result, char **f,
	const char c, const unsigned long flag)
{
	if (*f && c == (*f)[1])
	{
		*result |= flag;
		(*f)++;
		return (1);
	}
	return (0);
}

unsigned long	resolve_flags(char **s)
{
	unsigned long	result;
	unsigned long	l;

	result = 0;
	check_and_set(&result, s, '#', 16);
	check_and_set(&result, s, ' ', 128);
	check_and_set(&result, s, '-', 512);
	if (check_and_set(&result, s, '+', 256) == 1)
		result = result & ~128L;
	if (!(result & 512))
		check_and_set(&result, s, '0', 64);
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

unsigned long	resolve_len_flags(char **s)
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

int				check_conversion(char c)
{
	int		i;

	i = 0;
	while (i < RCOUNT)
	{
		if (c == resolvers[i].conversion)
			return (resolvers[i].type);
		i += 1;
	}
	return (0);
}

int				resolve(char **s, unsigned long *flags)
{
	int		result;

	if ((*s)[1] == '#' || (*s)[1] == '0' || (*s)[1] == '-' || (*s)[1] == '+' ||
		(*s)[1] == ' ' || (*s)[1] == '.' || ((*s)[1] >= '0' && (*s)[1] <= '9'))
		*flags += resolve_flags(s);
	if ((*s)[1] == 'l' || (*s)[1] == 'L' || (*s)[1] == 'h')
		*flags += resolve_len_flags(s);
	result = check_conversion((*s)[1]);
	*s += 1;
	return (result);
}
