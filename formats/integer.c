/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 10:49:27 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/10 20:38:09 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vaprintf.h"

int			write_ll(char f, long long v, unsigned long flags)
{
	char	*s[3];
	int		l;
	int		sg;
	int		m;
	char	q[2];

	l = (flags & 64L && !(flags & 512L)) ? (flags & (255LL << 56)) >> 56 : 0;
	l = (flags & 32L) ? (flags & (255LL << 48)) >> 48 : l;
	s[0] = "";
	if (f == 'd' || f == 'i')
		s[0] = itoa_base(v, 10, g_bstr);
	m = s[0][0] == '-' ? 1 : 0;
	sg = ((flags & 256L || flags & 128L) && m != 1) ? 1 : 0;
	s[1] = filler_s('0', l - len(s[0]) + (m == 1 && (flags & 32L) ? 1 : 0) -
		(!(flags & 32L) && (flags & 64L) ? sg : 0));
	q[0] = '\0';
	q[1] = '\0';
	if (m == 1)
		q[0] = '-';
	else if (flags & 384L)
		q[0] = flags & 128L ? ' ' : '+';
	s[2] = join(3, q, s[1], s[0][0] != '-' ? s[0] : &s[0][1]);
	write_flags_str(s[2], 0, flags, f);
	free_array(s, 3);
	return (0);
}

static char	*get_str(char f, unsigned long long v)
{
	char	*result;

	if (f == 'x' || f == 'X')
		result = itoa_base_u(v, 16, f == 'x' ? g_bstr : g_bstr_c);
	else if (f == 'u')
		result = itoa_base_u(v, 10, g_bstr);
	else if (f == 'o')
		result = itoa_base_u(v, 8, g_bstr);
	else if (f == 'b')
		result = itoa_base_u(v, 2, g_bstr);
	else
		result = NULL;
	return (result);
}

int			write_ull(char f, unsigned long long v, unsigned long flags)
{
	char	*s[4];
	int		l;

	l = (flags & 64L && !(flags & 512L)) ? (flags & (255LL << 56)) >> 56 : 0;
	l = (flags & 32L) ? (flags & (255LL << 48)) >> 48 : l;
	s[0] = (flags & 4096L && v == 0 && flags & 32L) ? NULL : get_str(f, v);
	s[1] = NULL;
	if ((flags & 16L && v != 0) || flags & 4096L)
	{
		if (f == 'o')
			s[1] = join(2, "0", "");
		else
			s[1] = join(2, f == 'x' ? "0x" : "0X", "");
	}
	s[2] = filler_s('0', l - len(s[0]) - (!(flags & 32L) && (flags & 64L) ?
		len(s[1]) : 0));
	s[3] = join(3, s[1], s[2], s[0]);
	write_flags_str(s[3], 0, flags, f);
	free_array(s, 4);
	return (0);
}
