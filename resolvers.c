/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolvers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 16:59:55 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/04 21:34:43 by emamenko         ###   ########.fr       */
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
	int				chg;

	result = 0;
	chg = 1;
	while (chg != 0)
	{
		if ((chg = check_and_set(&result, s, '+', 256)) == 1)
			result = result & ~128L;
		chg += check_and_set(&result, s, '#', 16);
		chg += check_and_set(&result, s, ' ', 128);
		chg += check_and_set(&result, s, '-', 512);
		chg += check_and_set(&result, s, '0', 64);
		if ((*s)[1] >= '1' && (*s)[1] <= '9')
		{
			*s += 1;
			l = atoi_s(s);
			result = (result & ~(255LL << 56)) | 1024 | (l << 56);
			chg += 1;
		}
		if ((*s)[1] == '.')
		{
			*s += 2;
			l = atoi_s(s);
			result = (result & ~(255LL << 48)) | 32 | (l << 48);
			chg += 1;
		}
	}
	return (result);
}

unsigned long	resolve_len_flags(char **s)
{
	long	result;

	result = 0;
	if ((*s)[1] == 'h')
		result |= ((*s)[2] == 'h' ? 2 : 1);
	else if ((*s)[1] == 'l' || (*s)[1] == 'j' || (*s)[1] == 'z')
		result |= ((*s)[2] == 'l' && (*s)[1] != 'j' && (*s)[1] != 'z' ? 8 : 4);
	else if ((*s)[1] == 'L')
		result |= 2048;
	*s += 1 + ((*s)[2] == 'h' || (*s)[2] == 'l' ? 1 : 0);
	return (result);
}

int				resolve(char **s, unsigned long *flags)
{
	int		result;
	int		i;

	while ((*s)[1] == '#' || (*s)[1] == '0' || (*s)[1] == '-' || (*s)[1] == ' '
		|| (*s)[1] == '.' || ((*s)[1] >= '0' && (*s)[1] <= '9') ||
		(*s)[1] == 'l' || (*s)[1] == 'L' || (*s)[1] == 'h' ||
		(*s)[1] == '+' || (*s)[1] == 'j' || (*s)[1] == 'z')
	{
		if ((*s)[1] == '#' || (*s)[1] == '0' || (*s)[1] == '-' ||
			(*s)[1] == '+' || (*s)[1] == ' ' || (*s)[1] == '.' ||
			((*s)[1] >= '0' && (*s)[1] <= '9'))
			*flags |= resolve_flags(s);
		if ((*s)[1] == 'l' || (*s)[1] == 'L' || (*s)[1] == 'h' ||
			(*s)[1] == 'j' || (*s)[1] == 'z')
			*flags |= resolve_len_flags(s);
	}
	i = -1;
	result = -1;
	while (++i < RCOUNT)
		if ((*s)[1] == g_resolvers[i].conversion)
			result = g_resolvers[i].type;
	*s += 1;
	return (result);
}
