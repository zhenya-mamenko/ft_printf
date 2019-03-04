/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vaprintf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:18:18 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/04 00:03:11 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAPRINTF_H
# define VAPRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "formats/ext.h"

# define LLONG_MAX	__LONG_LONG_MAX__
# define LLONG_MIN	(-__LONG_LONG_MAX__-1LL)
# define ULLONG_MAX	(__LONG_LONG_MAX__*2ULL+1ULL)

static const char	*g_bstr = "0123456789abcdef";
static const char	*g_bstr_c = "0123456789ABCDEF";

char				*vaprintf(const char *format, va_list av);
char				*itoa_base(long long value, int base,
						const char *base_str);
char				*itoa_base_u(unsigned long long value, int base,
						const char *base_str);
int					write_ll(char f, long long v, unsigned long flags);
int					write_ull(char f, unsigned long long v,
						unsigned long flags);
void				write_flags_str(char *s, int n, unsigned long flags,
						char ch);
int					write_str(const char *s);
int					write_str_n(const char *s, int l);
void				write_float(char f, long double v,
						unsigned long flags);
int					atoi_s(char **str);
int					filler(char c, int l);
char				*filler_s(char c, int l);
void				int_wrapper(va_list av, unsigned long flags, char type);
int					len(const char *s);
int					compare(const char *s1, const char *s2, size_t n);
void				*cpy(void *dst, const void *src, size_t n);
char				*join(int count, ...);
char				*substr(const char *s, int l);
void				render_format(char **f);
int					resolve(char **s, unsigned long *flags);
unsigned long		resolve_len_flags(char **s);
unsigned long		resolve_flags(char **s);
long double			dmodf(long double value, long double *iptr);
unsigned int		flen(long double v);
long double			pw(int l);
char				*ftoa(long double v);
void				non_printable(char *s, int l);

#endif
