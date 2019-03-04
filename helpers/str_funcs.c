/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 15:33:42 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/03 16:19:27 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vaprintf.h"

int		compare(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*b1;
	unsigned char	*b2;

	b1 = (unsigned char *)s1;
	b2 = (unsigned char *)s2;
	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (b1[i] != b2[i])
			return (b1[i] - b2[i]);
		i += 1;
	}
	if (i == n)
		return (0);
	if (s1[i] == '\0' || s2[i] == '\0')
	{
		return (b1[i] - b2[i]);
	}
	return (0);
}

int		len(const char *s)
{
	int		l;

	l = 0;
	while (s && s[l])
		l += 1;
	return (l);
}

void	*cpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (n == 0)
		n = len((char *)src);
	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i += 1;
	}
	return (dst);
}

char	*join(int count, ...)
{
	va_list		av;
	char		*result;
	char		*a[100];
	int			i;
	int			l;

	va_start(av, count);
	i = -1;
	l = 0;
	while (++i < count)
	{
		a[i] = va_arg(av, char*);
		l += len(a[i]);
	}
	va_end(av);
	result = malloc(sizeof(char) * (l + 1));
	result[l] = '\0';
	i = -1;
	l = 0;
	while (++i < count)
	{
		cpy(result + l, a[i], len(a[i]));
		l += len(a[i]);
	}
	return (result);
}

char	*substr(const char *s, int l)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (l + 1));
	tmp[l] = '\0';
	cpy(tmp, s, l);
	return (tmp);
}
