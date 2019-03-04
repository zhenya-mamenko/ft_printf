/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vaprintf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 16:08:27 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/03 16:08:27 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

extern char	*vaprintf(const char *format, va_list av);

int			ft_printf(const char *format, ...);
char		*ft_sprintf(const char *format, ...);

#endif
