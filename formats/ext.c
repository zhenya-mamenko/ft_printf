/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:28:28 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/03 16:19:27 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vaprintf.h"

static t_format	get_format(const char *s, const int l)
{
	int		i;

	i = 0;
	while (i < FCOUNT)
	{
		if (compare(g_formats[i].abbr, s, l) == 0)
			return (g_formats[i]);
		i += 1;
	}
	return (g_formats[3]);
}

static void		process_format(const char *s, const int l)
{
	t_format	f;
	char		*ss;
	int			ll[3];

	if (l <= 0)
		return ;
	f = get_format(s, l);
	ll[0] = len(ESC);
	ll[1] = len(f.code);
	ll[2] = len(TERM);
	ss = malloc(sizeof(char) * (ll[0] + ll[1] + ll[2] + 1));
	ss[ll[0] + ll[1] + ll[2]] = '\0';
	cpy(ss, ESC, 0);
	cpy(ss + ll[0], f.code, 0);
	cpy(ss + ll[0] + ll[1], TERM, 0);
	write_str(ss);
	free(ss);
}

void			render_format(char **f)
{
	int		b;
	int		i;

	b = 1;
	i = 1;
	while ((*f)[i] && (*f)[i] != '~')
	{
		if ((*f)[i] == ';')
		{
			process_format((const char *)((*f) + b), i - b);
			b = i + 1;
		}
		i += 1;
	}
	process_format((const char *)((*f) + b), i - b);
	(*f) += i;
}
