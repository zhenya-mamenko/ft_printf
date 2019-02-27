/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_u.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:30:12 by emamenko          #+#    #+#             */
/*   Updated: 2019/02/26 22:53:48 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	len(unsigned long long value, int base)
{
	int		l;

	l = value <= 0 ? 1 : 0;
	while (value != 0)
	{
		l++;
		value /= base;
	}
	return (l);
}

static void	to_base(char *r, unsigned long long value, int base, char *b_str)
{
	*r = b_str[value % base];
	r--;
	value /= base;
	if (value >= (unsigned int)base)
		to_base(r, value, base, b_str);
	else
		*r = b_str[value];
}

char		*ft_itoa_base_u(unsigned long long value, int base, char *base_str)
{
	char	*result;
	char	*s;
	int		l;

	l = len(value, base);
	result = malloc(sizeof(char) * (l + 1));
	s = result;
	result[l] = '\0';
	to_base(result + l - 1, value, base, base_str);
	return (s);
}
