/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vaprintf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:24:06 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/03 16:05:16 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAPRINTF_H
# define VAPRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "formats/ext.h"

static const char	*g_bstr = "0123456789abcdef";
static const char	*g_bstr_c = "0123456789ABCDEF";

char				*vaprintf(const char *format, va_list av);
char				*itoa_base(long long value, int base, const char *base_str);
char				*itoa_base_u(unsigned long long value, int base, const char *base_str);
int					write_ll(char f, long long v, unsigned long flags);
int					write_ull(char f, unsigned long long v, unsigned long flags);
void				write_flags_str(char *s, int n, unsigned long flags, char ch);
void				write_str(const char *s);
void				write_str_n(const char *s, int l);
void				write_float(char f, long double v, unsigned long flags);
int					atoi_s(char **str);
void				filler(char c, int l);
int					len(const char *s);
int					compare(const char *s1, const char *s2, size_t n);
void				*cpy(void *dst, const void *src, size_t n);
char				*join(int count, ...);
char				*substr(const char *s, int l);
void				render_format(char **f);

#endif
