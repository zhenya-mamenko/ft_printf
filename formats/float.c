/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 12:13:29 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/10 20:35:28 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vaprintf.h"

char		*xfloat(long double v)
{
	int		sign;
	char	*t;
	char	*tt;

	sign = (v < 0) ? 1 : 0;
	v = (v < 0) ? -v : v;
	if (v <= ULLONG_MAX)
	{
		t = itoa_base_u((unsigned long long)v, 10, "0123456789");
		tt = join(2, (sign == 1) ? "-" : "", t);
		free(t);
		return (tt);
	}
	else
		return (ftoa(v));
}

void		write_float(char f, long double v, unsigned long flags)
{
	unsigned long long	l;
	unsigned long long	i;
	char				*res[5];
	long double			t[3];

	t[0] = dmodf(v, &t[1]);
	res[0] = xfloat(t[1]);
	res[4] = NULL;
	if (res[0][0] != '-' && flags & 384L)
		res[4] = join(2, flags & 128L ? " " : "+", "");
	l = (flags & 32L) ? (flags & (255LL << 48)) >> 48 : 6;
	if ((t[0] == 0.0L && l == 0) || l == 0)
		res[1] = (flags & 16L) ? join(2, "", "") : NULL;
	else
	{
		i = l;
		while (i-- > 0)
			t[0] *= 10.0L;
		res[1] = xfloat(t[0] + 0.5L);
	}
	res[2] = filler_s('0', l - len(res[1]));
	res[3] = join(5, res[4], res[0], res[1] != NULL ? "." : "", res[2], res[1]);
	write_flags_str(res[3], 0, flags, f);
	free_array(res, 5);
}
