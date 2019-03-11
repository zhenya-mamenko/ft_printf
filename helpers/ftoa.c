/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 20:50:43 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/10 20:18:07 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vaprintf.h"

long double		dmodf(long double value, long double *iptr)
{
	long double	max;
	int			sign;

	sign = 1.0L;
	if (value < 0.0L)
	{
		sign = -1.0L;
		value = -value;
	}
	max = 1.844674407370955e19L;
	if (value >= max)
		*iptr = sign * value;
	else
	{
		*iptr = value + max;
		*iptr -= max;
		while (*iptr > value)
			*iptr -= 1.0L;
		*iptr *= sign;
	}
	return (value - *iptr * sign);
}

unsigned int	flen(long double v)
{
	unsigned int	i;
	long double		t;

	i = (v == 0.0L) ? 1 : 0;
	if (v < 0.0L)
		v = -v;
	dmodf(v, &t);
	while (t >= 1.0L)
	{
		i += 1;
		t /= 10.0L;
	}
	return (i);
}

long double		pw(int l)
{
	long double	result;

	result = 1.0L;
	while (l-- > 0)
	{
		result *= 10.0L;
	}
	return (result);
}

char			*ftoa(long double v)
{
	unsigned int	l;
	unsigned int	i;
	char			*result;
	long double		d;
	long double		t;

	i = v < 0 ? 1 : 0;
	l = flen(v) + i;
	result = malloc(sizeof(char) * (l + 1));
	result[l] = '\0';
	if (v < 0)
	{
		result[0] = '-';
		v = -v;
	}
	d = pw(l - i - 1);
	while (i < l)
	{
		t = v / d;
		result[i] = (int)t + '0';
		v = v - d * (int)t;
		d /= 10.0L;
		i += 1;
	}
	return (result);
}
