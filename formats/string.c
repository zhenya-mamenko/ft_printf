/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:43:23 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/03 16:19:27 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vaprintf.h"

extern char	*g_output;

void		write_str_n(const char *s, int l)
{
	char	*tmp;
	char	*ss;

	ss = substr(s, l);
	tmp = join(2, g_output, ss);
	free(g_output);
	free(ss);
	g_output = tmp;
}

void		write_str(const char *s)
{
	write_str_n(s, len(s));
}

void		write_flags_str(char *s, int n, unsigned long f, char ch)
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
			write_str(" ");
		write_str_n(s, l);
		return ;
	}
	if ((f & 512))
	{
		if (sign == 1)
			write_str("+");
		if (w[1] > l && ch != 's')
			filler('0', w[1] - l);
		write_str_n(s, l);
		filler(c, w[0] - (l > w[1] ? l : w[1]));
	}
	else
	{
		filler(c, w[0] - (l > w[1] ? l : w[1]) - sign);
		if (sign == 1)
			write_str("+");
		if (w[1] > l && ch != 's')
			filler('0', w[1] - l);
		write_str_n(s, l);
	}
}
