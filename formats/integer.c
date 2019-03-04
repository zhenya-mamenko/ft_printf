/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 10:49:27 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/03 16:19:27 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vaprintf.h"

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
		if (f == 'o')
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
