/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 12:13:29 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/03 20:06:49 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vaprintf.h"

static long double	dmodf(long double value, long double *iptr)
{
	long double	max;

	max = 1.844674407370955e19L;
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
	while (t >= 1.0L)
	{
		i += 1;
		t /= 10.0L;
	}
	return (i);
}

static void			to_s(long double v, char *s)
{
	long double	t;

	dmodf(v / 10, &t);
	if (t >= 1.0L)
	{
		to_s(t, s - 1);
		t = v - t * 10.0L;
		while (t >= 10.0L)
			t -= 10.0L;
		while (t < 0.0L)
			t += 10.0L;
		*s = (char)(t) + '0';
	}
	else
		*s = '0' + (char)v;
}

void				write_float(char f, long double v, unsigned long flags)
{
	unsigned long long	l;
	unsigned long long	i;
	char				*res[4];
	long double			t;

	l = flen(v) + (v < 0 ? 1 : 0) + (f == 'f' ? 0 : 0);
	res[0] = malloc(sizeof(char) * (l + 1));
	res[0][l] = '\0';
	if (v < 0)
	{
		res[0][0] = '-';
		v = -v;
	}
	t = dmodf(v, &t);
	while (t >= 1.0L)
		t -= 1.0L;
	to_s(v, res[0] + l - 1);
	l = (flags & 32) ? (flags & (255LL << 48)) >> 48 : 6;
	if ((t == 0.0L && l == 0) || l == 0)
	{
		res[1] = (flags & 16) ? "0" : NULL;
	}
	else
	{
		i = l;
		while (i-- > 0)
			t *= 10.0L;
		res[1] = itoa_base_u((unsigned long)(t + 0.5L), 10, "0123456789");
	}
	res[2] = filler_s('0', l - len(res[1]));
	res[3] = join(4, res[0], res[1] != NULL ? "." : "", res[2], res[1]);
	write_flags_str(res[3], 0, flags, 'f');
	free(res[0]);
	if (res[1] && l != 0)
		free(res[1]);
	if (res[2])
		free(res[2]);
	free(res[3]);
}
