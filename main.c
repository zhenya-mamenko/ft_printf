#include "ft_printf.h"
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	void	*p;

	ft_printf("\n%~flcyan;u;~Start testing%~-a~\n\n");
	p = malloc(1);
	if (ac == 2)
	{
		printf("%s\n", av[1]);
	}

	ft_printf("%c\n", 'A');
	ft_printf("ft_printf -- p=%p, i=%hhi, d=% d, o=%ho, u=%lu, x=%llx, X=%X, #o=%#o\n", p, (char)-123, 456, (unsigned short)177789,
		(unsigned long)123, (unsigned long long)9223372036854775807LL, 255, 64);
	printf("printf    -- p=%p, i=%hhi, d=% d, o=%ho, u=%lu, x=%llx, X=%X, #o=%#o\n", p, (char)-123, 456, (unsigned short)177789,
		(unsigned long)123, (unsigned long long)9223372036854775807LL, 255, 64);

	ft_printf("ft_printf -- |%10.5s| % 8d|\n", "123456789", 123987);
	printf("printf    -- |%10.5s| % 8d|\n", "123456789", 123987);

	ft_printf("ft_printf -- binary=%015b\n", 160);

	long double ld = 0.12345678901234567890123456789L;
	//printf("%.10Lf\n", __LDBL_MAX__);
/*	long long ll = (long long)ld;

	printf("f=%.20f\nLf=%.20Lf\nlast digit = %Lf\nf=%.30f\nlong=%llu\n",
		123456789012345678901234567890123456789.12345678901234567890,
		ld,
		ld - (ld / 10),
		0.12345678901234567890123456789,
		ll);
*/
	printf("%.22Lf|\n", ld);
	ft_printf("%.22Lf|\n", ld);
	printf("%.0Lf\n", 18446744073709551615.0L);
	ft_printf("%.0Lf\n", 18446744073709551615.0L);
/*
	int i = 0;
	while (i < 39)
	{
		printf("%s = "ESC"%s"TERM"%s"ESC"0"TERM"\n",
			g_formats[i].abbr, g_formats[i].code, g_formats[i].description);
		i += 1;
	}
*/
	ft_printf("%~fyellow;u;s~%s %~-u;blgreen;flred~ Test change %~-a~ normal\n",
		"It's works!");

}
