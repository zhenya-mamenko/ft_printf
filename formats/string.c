/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:43:23 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/04 22:14:35 by emamenko         ###   ########.fr       */
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
	while (g_outlen + l > slen)
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

	c = (f & 64) && !(f & 512) && !(f & 32) ? '0' : ' ';
	w[2] = w[5];
	if (x != 's')
		w[2] = (w[5] > w[1] ? w[5] : w[1]) + w[4];
	if (!(f & 512))
		filler(c, w[0] - w[2]);
	w[3] = (w[4] == 1) ? write_str("+") : 0;
	w[3] = (w[1] > w[5] && x != 's') ?
		filler('0', w[1] - w[5]) : 0;
	write_str_n(s, w[5]);
	if (f & 512)
		filler(c, w[0] - w[2]);
}

void		write_flags_str(char *s, int n, unsigned long f, char x)
{
	int		w[7];

	w[6] = len(s);
	w[4] = ((f & 256) && (x == 'i' || x == 'd') && s[0] != '-') ? 1 : 0;
	w[5] = n != 0 && (w[6] > n || (x == 'c' && s[0] == '\0')) ? n : w[6];
	w[0] = (f & 1024) ? (f & (255LL << 56)) >> 56 : 0;
	w[1] = (f & 32) && x != 'c' ? (f & (255LL << 48)) >> 48 : 0;
	if ((f & 32) && w[1] == 0 && w[6] == 1 && s[0] == '0' &&
		!((f & 16) && x == 'o'))
	{
		free(s);
		s = join(2, w[0] != 0 ? " " : "", "");
		w[5] = len(s);
	}
	if (w[0] <= (w[5] - (x == 'c' && w[6] == 2 ? 1 : 0) + w[4]) && w[1] < w[5])
	{
		if ((f & 384) && (x == 'i' || x == 'd' || x == 'f') && s[0] != '-')
			write_str((w[4] == 1) ? "+" : " ");
		write_str_n(s, w[5]);
		return ;
	}
	write_sub(w, s, f, x);
}
