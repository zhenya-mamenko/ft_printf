/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_funcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:45:31 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/03 16:40:51 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vaprintf.h"

void	filler(char c, int l)
{
	int		i;
	char	*s;

	s = malloc(sizeof(char) * (l + 1));
	s[l] = '\0';
	i = 0;
	while (i < l)
	{
		s[i] = c;
		i += 1;
	}
	write_str(s);
	free(s);
}
