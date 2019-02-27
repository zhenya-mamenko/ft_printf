/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 10:49:27 by emamenko          #+#    #+#             */
/*   Updated: 2019/02/27 11:48:41 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	len(char *s)
{
	int		l;

	l = 0;
	while (s[l])
		l += 1;
	return (l);
}

void		write_str(char *s)
{
	write(1, s, len(s));
}

void		write_ll(char f, long long v)
{
	char	*s;

	if (f == 'd' || f == 'i')
		s = ft_itoa_base(v, 10, g_bstr);
	else
		return ;
	write_str(s);
}

void		write_ull(char f, unsigned long long v)
{
	char	*s;

	if (f == 'x' || f == 'X')
		s = ft_itoa_base_u(v, 16, f == 'x' ? g_bstr : g_bstr_c);
	else if (f == 'y' || f == 'Y')
	{
		write_str(f == 'y' ? "0x" : "0X");
		s = ft_itoa_base_u(v, 16, f == 'y' ? g_bstr : g_bstr_c);
	}
	else if (f == 'u')
		s = ft_itoa_base_u(v, 10, g_bstr);
	else if (f == 'o')
		s = ft_itoa_base_u(v, 8, g_bstr);
	else if (f == 'b')
		s = ft_itoa_base_u(v, 2, g_bstr);
	else
		return ;
	write_str(s);
}