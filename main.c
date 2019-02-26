#include "ft_printf.h"

int main(int ac, char **av)
{
	if (ac != 1)
		ft_printf(av[1]);
		ft_printf("\n");
}
