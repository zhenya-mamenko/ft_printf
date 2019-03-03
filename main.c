#include "ft_printf.h"
#include <stdio.h>

int main(int ac, char **av)
{
	void	*p;

	p = malloc(1);
	if (ac == 2)
	{
		printf("%s\n", av[1]);
	}
	ft_printf("ft_printf -- p=%p, i=%hhi, d=%d, o=%ho, u=%lu, x=%llx, X=%X, #o=%#o\n", p, (char)-123, -456, (unsigned short)177789,
		(unsigned long)123, (unsigned long long)9223372036854775807LL, 255, 64);
	printf("printf    -- p=%p, i=%hhi, d=%d, o=%ho, u=%lu, x=%llx, X=%X, #o=%#o\n", p, (char)-123, -456, (unsigned short)177789,
		(unsigned long)123, (unsigned long long)9223372036854775807LL, 255, 64);

	ft_printf("ft_printf -- |%10.5s| % 8d|\n", "123456789", 123987);
	printf("printf    -- |%10.5s| % 8d|\n", "123456789", 123987);

	ft_printf("ft_printf -- binary=%015b\n", 160);

	long double ld = -12345678901234567890123456789.001234567890L;
	//printf("%.10Lf\n", __LDBL_MAX__);
	/*long long ll = (long long)ld;

	printf("f=%80.20f\nLf=%.20Lf\nlast digit = %Lf\nf=%.30f\nlong=%llu",
		123456789012345678901234567890123456789.12345678901234567890,
		ld,
		ld - (ld / 10),
		0.12345678901234567890123456789,
		ll);
		*/
	printf("%.5Lf\n", ld);
	ft_printf("%.5Lf\n", ld);
}
