/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:30:12 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/03 22:37:08 by emamenko         ###   ########.fr       */
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

char		*itoa_base(long long val, int base, const char *base_str)
{
	char	*result;
	char	*s;
	int		l;

	l = len_base(val >= 0 ? val : -(val / 10), base) + (val < 0 ? 2 : 0);
	result = malloc(sizeof(char) * (l + 1));
	s = result;
	result[l] = '\0';
	if (base == 10 && val < 0)
	{
		*result = '-';
		result++;
		l--;
		if (val == LLONG_MIN)
		{
			*result = '9';
			result++;
			l--;
			val = 223372036854775808LL;
		}
		else
			val = -val;
	}
	to_base_u(result + l - 1, (unsigned long long)val, base, base_str);
	return (s);
}
