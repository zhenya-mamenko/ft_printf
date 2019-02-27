#include "ft_printf.h"

int main(int ac, char **av)
{
	ft_printf("%s\n", ft_itoa_base(9223372036854775807LL, 16, "0123456789ABCDEF"));
	if (ac != 1)
		ft_printf("%s - 100%%\n", av[1]);
}
