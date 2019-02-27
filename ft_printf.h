/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:24:06 by emamenko          #+#    #+#             */
/*   Updated: 2019/02/27 11:48:41 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

static char	*g_bstr = "0123456789abcdef";
static char	*g_bstr_c = "0123456789ABCDEF";

int			ft_printf(const char *format, ...);
char		*ft_itoa_base(long long value, int base, char *base_str);
char		*ft_itoa_base_u(unsigned long long value, int base, char *base_str);
void		write_ll(char f, long long v);
void		write_ull(char f, unsigned long long v);
void		write_str(char *s);

#endif
