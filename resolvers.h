/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolvers.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 23:26:49 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/10 13:23:45 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOLVERS_H
# define RESOLVERS_H

# define RCOUNT 18

typedef struct	s_resolve
{
	char		conversion;
	int			type;
}				t_resolve;

t_resolve		g_resolvers[RCOUNT] = {
	{'%', 1},
	{'s', 2},
	{'c', 3},
	{'p', 4},
	{'d', 5},
	{'i', 5},
	{'o', 5},
	{'u', 5},
	{'X', 5},
	{'x', 5},
	{'b', 5},
	{'f', 6},
	{'~', 7},
	{'r', 8},
	{'R', 8},
	{'D', 5},
	{'O', 5},
	{'U', 5}
};

#endif
