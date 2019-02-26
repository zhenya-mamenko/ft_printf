/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:26:32 by emamenko          #+#    #+#             */
/*   Updated: 2019/02/25 22:11:41 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_simple(char *s, int len)
{
	write(1, s, len);
}

int		ft_printf(const char *format, ...)
{
	va_list		av;

	va_start(av, format);
	va_end(av);
}
