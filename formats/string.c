/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:43:23 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/03 18:14:34 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vaprintf.h"

extern char	*g_output;

int		write_str_n(const char *s, int l)
{
	char	*tmp;
	char	*ss;

	ss = substr(s, l);
	tmp = join(2, g_output, ss);
	free(g_output);
	free(ss);
	g_output = tmp;
	return (l);
}

int		write_str(const char *s)
{
	int		l;

	l = len(s);
	write_str_n(s, l);
	return (l);
}

void	write_flags_str(char *s, int n, unsigned long f, char ch)
{
	int		l;
	int		w[2];
	char	c;
	int		sign;
	int		tmp;

	sign = ((f & 256) && (ch == 'i' || ch == 'd') && s[0] != '-') ? 1 : 0;
	l = n != 0 && len(s) > n ? n : len(s);
	w[0] = (f & 1024) ? (f & (255LL << 56)) >> 56 : 0;
	w[1] = (f & 32) ? (f & (255LL << 48)) >> 48 : 0;
	c = f & 64 ? '0' : ' ';
	if (w[0] <= l && w[1] < l)
	{
		if ((f & 384) && (ch == 'i' || ch == 'd' || ch == 'f') && s[0] != '-')
			write_str((sign == 1) ? "+" : " ");
		write_str_n(s, l);
		return ;
	}
	if (!(f & 512))
		filler(c, w[0] - (l > w[1] ? l : w[1]) - sign);
	tmp = (sign == 1) ? write_str("+") : 0;
	tmp = (w[1] > l && ch != 's') ? filler('0', w[1] - l) : 0;
	write_str_n(s, l);
	if (f & 512)
		filler(c, w[0] - (l > w[1] ? l : w[1]));
}
