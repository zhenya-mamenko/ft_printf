/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:24:06 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/02 18:45:56 by emamenko         ###   ########.fr       */
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
char		*itoa_base(long long value, int base, char *base_str);
char		*itoa_base_u(unsigned long long value, int base, char *base_str);
int			write_ll(char f, long long v, unsigned long flags);
int			write_ull(char f, unsigned long long v, unsigned long flags);
void		write_flags_str(char *s, int n, unsigned long flags, char ch);
void		write_str(char *s);
void		write_float(char f, long double v, unsigned long flags);
int			atoi_s(char **str);
void		filler(char c, int l);
int			len(char *s);

#endif
