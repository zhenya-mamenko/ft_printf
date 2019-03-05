/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:30:12 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/04 21:15:41 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vaprintf.h"

static int	len_base(unsigned long long value, int base)
{
	int		l;

	l = (value == 0) ? 1 : 0;
	while (value != 0)
	{
		l++;
		value /= base;
	}
	return (l);
}

static void	to_base_u(char *r, unsigned long long value, int base,
	const char *b_str)
{
	*r = b_str[value % base];
	r--;
	if (value < (unsigned int)base)
		return ;
	value /= base;
	if (value >= (unsigned int)base)
		to_base_u(r, value, base, b_str);
	else
		*r = b_str[value];
}

char		*itoa_base_u(unsigned long long value, int base,
	const char *base_str)
{
	char	*result;
	char	*s;
	int		l;

	l = len_base(value, base);
	result = malloc(sizeof(char) * (l + 1));
	s = result;
	result[l] = '\0';
	to_base_u(result + l - 1, value, base, base_str);
	return (s);
}

char		*itoa_base(long long v, int base, const char *base_str)
{
	char	*s[2];
	int		l;

	l = len_base(v >= 0 ? v : -(v / 10), base) +
		(v < 0 ? 1 : 0) + (v <= -10 ? 1 : 0);
	s[0] = malloc(sizeof(char) * (l + 1));
	s[1] = s[0];
	s[0][l] = '\0';
	if (base == 10 && v < 0)
	{
		*s[0] = '-';
		s[0]++;
		l--;
		if (v == LLONG_MIN)
		{
			*s[0] = '9';
			s[0]++;
			l--;
			v = 223372036854775808LL;
		}
		else
			v = -v;
	}
	to_base_u(s[0] + l - 1, (unsigned long long)v, base, base_str);
	return (s[1]);
}
