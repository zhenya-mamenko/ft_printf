/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:17:47 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/04 20:26:43 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

extern int	vaprintf(char **s, const char *format, va_list av);

int			ft_printf(const char *format, ...);
int			ft_printf_fd(int fd, const char *format, ...);
int			ft_sprintf(char **s, const char *format, ...);

#endif
