/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 10:49:27 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/02 18:43:46 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		len(char *s)
{
	int		l;

	l = 0;
	while (s[l])
		l += 1;
	return (l);
}

void	write_str(char *s)
{
	write(1, s, len(s));
}

void	write_flags_str(char *s, int n, unsigned long f, char ch)
{
	int		l;
	int		w[2];
	char	c;
	int		sign;

	sign = ((f & 256) && (ch == 'i' || ch == 'd') && s[0] != '-') ? 1 : 0;
	l = n != 0 && len(s) > n ? n : len(s);
	w[0] = (f & 1024) ? (f & (255LL << 56)) >> 56 : 0;
	w[1] = (f & 32) ? (f & (255LL << 48)) >> 48 : 0;
	c = f & 64 ? '0' : ' ';
	if (w[0] <= l && w[1] < l)
	{
		if ((f & 256) && (ch == 'i' || ch == 'd' || ch == 'f') && s[0] != '-')
			write(1, " ", 1);
		write(1, s, l);
	}
	else
	{
		if ((f & 512))
		{
			if (sign == 1)
				write(1, "+", 1);
			if (w[1] > l && ch != 's')
				filler('0', w[1] - l);
			write(1, s, l);
			filler(c, w[0] - (l > w[1] ? l : w[1]));
		}
		else
		{
			filler(c, w[0] - (l > w[1] ? l : w[1]) - sign);
			if (sign == 1)
				write(1, "+", 1);
			if (w[1] > l && ch != 's')
				filler('0', w[1] - l);
			write(1, s, l);
		}
	}
}

int		write_ll(char f, long long v, unsigned long flags)
{
	char	*s;

	if (f == 'd' || f == 'i')
		s = itoa_base(v, 10, g_bstr);
	else
		s = (flags != 65535) ? "" : "";
	write_flags_str(s, 0, flags, f);
	free(s);
	return (0);
}

int		write_ull(char f, unsigned long long v, unsigned long flags)
{
	char	*s;

	if (flags & 16)
	{
		if ( f == 'o')
			write_str("0");
		else
			write_str(f == 'x' ? "0x" : "0X");
	}
	if (f == 'x' || f == 'X')
		s = itoa_base_u(v, 16, f == 'x' ? g_bstr : g_bstr_c);
	else if (f == 'u')
		s = itoa_base_u(v, 10, g_bstr);
	else if (f == 'o')
		s = itoa_base_u(v, 8, g_bstr);
	else if (f == 'b')
		s = itoa_base_u(v, 2, g_bstr);
	else
		return (1);
	write_flags_str(s, 0, flags, f);
	free(s);
	return (0);
}