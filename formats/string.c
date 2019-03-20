/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:43:23 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/20 15:33:51 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vaprintf.h"

extern char	*g_output;
extern int	g_outlen;

void		memjoin(char *dst, const char *src, int l)
{
	int		i;

	i = 0;
	while (i < l)
	{
		dst[i] = src[i];
		i += 1;
	}
}

int			write_str_n(const char *s, int l)
{
	static int	slen = BUFFSIZE;
	char		*tmp;
	int			f;

	if (l == 0)
		return (0);
	f = 0;
	while (g_outlen + l >= slen)
	{
		slen += BUFFSIZE;
		f = 1;
	}
	tmp = (f == 1) ? malloc(sizeof(char) * slen) : g_output;
	memjoin(tmp, g_output, g_outlen);
	memjoin(tmp + g_outlen, s, l);
	if (f == 1)
		free(g_output);
	g_outlen += l;
	g_output = tmp;
	return (l);
}

int			write_str(const char *s)
{
	int		l;

	l = len(s);
	write_str_n(s, l);
	return (l);
}

static void	write_sub(int *w, char *s, unsigned long f, char x)
{
	char	c;

	c = (f & 64L) && !(f & 512L) && !(f & 32L) ? '0' : ' ';
	w[2] = w[5];
	if (x != 's')
		w[2] = (w[5] > w[1] ? w[5] : w[1]) + w[4];
	if (!(f & 512L))
		filler(c, w[0] - w[2]);
	w[3] = (w[1] > w[5] && x != 's') ?
		filler('0', w[1] - w[5]) : 0;
	write_str_n(s, w[5]);
	if (f & 512L)
		filler(c, w[0] - w[2]);
}

void		write_flags_str(char *s, int n, unsigned long f, char x)
{
	int		w[7];

	w[6] = len(s);
	w[4] = 0;
	w[5] = n != 0 && (w[6] > n || (x == 'c' && s[0] == '\0')) ? n : w[6];
	w[0] = (f & 1024L) ? (f & (255LL << 56)) >> 56 : 0;
	w[1] = (f & 32L) && x != 'c' ? (f & (255LL << 48)) >> 48 : 0;
	if ((f & 32L) && w[1] == 0 && w[6] == 1 && s[0] == '0' &&
		!((f & 16L) && x == 'o') && !(x == 'f' && (f & 32L) && w[1] == 0))
	{
		free(s);
		s = join(2, w[0] != 0 ? " " : "", "");
		w[5] = len(s);
	}
	w[5] = (w[1] == 0 && (f & 32L) && x == 's') ? 0 : w[5];
	if (w[0] <= (w[5] + w[4]) && w[1] < w[5])
	{
		write_str_n(s, w[5]);
		return ;
	}
	write_sub(w, s, f, x);
}
