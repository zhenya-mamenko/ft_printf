#include "ft_printf.h"
#include <stdio.h>

int main(int ac, char **av)
{
	void	*p;

	ft_printf("test\n");
	p = malloc(1);
	ft_printf("%s\n", ft_itoa_base(9223372036854775807LL, 16, g_bstr_c));
	if (ac != 1)
	{
		ft_printf("%s - 100%%\n%c\n", av[1], 'A');
	}
	ft_printf("ft_printf -- p=%p, i=%hhi, d=%d, o=%ho, u=%lu, x=%llx, X=%X\n", p, (char)-123, -456, (unsigned short)177789,
		(unsigned long)123, (unsigned long long)9223372036854775807LL, 255);
	printf("printf    -- p=%p, i=%hhi, d=%d, o=%ho, u=%lu, x=%llx, X=%X\n", p, (char)-123, -456, (unsigned short)177789,
		(unsigned long)123, (unsigned long long)9223372036854775807LL, 255);
	ft_printf("ft_printf -- binary=%b\n", 160);
}
