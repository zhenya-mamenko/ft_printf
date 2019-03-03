/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 12:13:29 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/02 18:49:42 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long double	dmodf(long double value, long double *iptr)
{
	long double	max;

	max = (long double)((unsigned long long)-1);
	if (value >= max)
		*iptr = value;
	else
	{
		*iptr = value + max;
		*iptr -= max;
		while (*iptr > value)
			*iptr -= 1.0L;
	}
	return (value - *iptr);
}

static unsigned int	flen(long double v)
{
	unsigned int	i;
	long double		t;

	i = (v == 0.0L) ? 1 : 0;
	if (v < 0.0L)
		v = -v;
	dmodf(v, &t);
	while ((t - 1.0L) > __LDBL_EPSILON__)
	{
		i += 1;
		t /= 10.0L;
	}
	return (i);
}

static void			to_s(long double v, char *s)
{
	long double	t;

	if (((v / 10) - 1.0L) > __LDBL_EPSILON__)
	{
		dmodf(v / 10, &t);
		to_s(t, s - 1);
		t = v - t * 10;
		while (t >= 10)
		{
			t -= 10;
			*(s - 1) += 1;
		}
		*s = (char)(t) + '0';
	}
	else
		*s = '0' + (char)v;
}

void				write_float(char f, long double v, unsigned long flags)
{
	unsigned long long	l;
	unsigned long long	i;
	char				*res;
	long double			t;

	if (f == ' ' && v == 0 && flags == 0)
		;
	l = flen(v) + (v < 0 ? 1 : 0);
	res = malloc(sizeof(char) * (l + 1));
	res[l] = '\0';
	if (v < 0)
	{
		res[0] = '-';
		v = -v;
	}
	t = dmodf(v, &t);
	to_s(v, res + l - 1);
	write_str(res);
	free(res);
	l = (flags & 32) ? (flags & (255LL << 48)) >> 48 : 6;
	if ((t == 0.0L && l == 0) || l == 0)
	{
		if (flags & 16)
			write_str(".0");
		return ;
	}
	i = l;
	while (i-- > 0)
		t *= 10;
	write_str(".");
	res = itoa_base_u((unsigned long)(t + 0.5), 10, "0123456789");
	i = l - len(res);
	while (i-- > 0)
		write_str("0");
	write_str(res);
	free(res);
}
