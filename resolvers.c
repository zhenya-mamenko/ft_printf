/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolvers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 16:59:55 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/03 17:06:26 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vaprintf.h"

static void		check_and_set(unsigned long *result, char *f, char c,
	unsigned long flag)
{
	if (c == *f)
		*result |= flag;
	f++;
}

unsigned long	resolve_flags(char **s)
{
	unsigned long	result;
	unsigned long	l;

	result = 0;

	check_and_set(&result, )
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

int				resolve(char **s, unsigned long *flags)
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
