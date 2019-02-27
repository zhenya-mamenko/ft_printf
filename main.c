#include "ft_printf.h"
#include <stdio.h>

int main(int ac, char **av)
{
	void	*p;

	p = malloc(1);
	ft_printf("%s\n", ft_itoa_base(9223372036854775807LL, 16, g_bstr_c));
	if (ac != 1)
	{
		ft_printf("%s - 100%%\n%c\n", av[1], 'A');
	}
	ft_printf("ft_printf -- p=%p, i=%i, d=%d, o=%o, u=%u, x=%x, X=%X\n", p, -123, -456, 789, 123, 255, 255);
	printf("printf    -- p=%p, i=%i, d=%d, o=%o, u=%u, x=%x, X=%X\n", p, -123, -456, 789, 123, 255, 255);
	ft_printf("ft_printf -- binary=%b\n", 160);
}
