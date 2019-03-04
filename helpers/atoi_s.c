/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 15:33:42 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/03 16:19:27 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vaprintf.h"

static int	check(char c, int f, long v)
{
	int		result;
	int		r;

	result = c >= '0' && c <= '9' ? 0 : 3;
	result = (c == '+' || c == '-') ? 1 : result;
	result = (c == ' ' || c == '\n' || c == '\t' || c == '\r' ||
		c == '\v' || c == '\f') ? 2 : result;
	r = f < result ? -1 : result;
	if (result == 0 && (v < 0 ? -v : v) >= 922337203685477580)
	{
		if ((v < 0 ? -v : v) == 922337203685477580)
		{
			if ((v < 0 && (c - '0') > 8) || (v > 0 && (c - '0') > 7))
				r = -100;
		}
		else
			r = -100;
	}
	return (r);
}

int			atoi_s(char **str)
{
	long	result;
	int		f;
	int		r;
	int		n;

	result = 0;
	f = 2;
	n = 1;
	while (**str)
	{
		r = check(**str, f, result);
		if (r == -100)
			return (result < 0 ? 0 : -1);
		else if (r == -1)
			break ;
		else if (r == 1)
			n = **str == '-' ? -1 : 1;
		else if (r == 0)
			result = result * 10 + (**str - '0') * n;
		f = (r == 1 || r == 0) ? 0 : f;
		(*str)++;
	}
	(*str)--;
	return (result);
}
