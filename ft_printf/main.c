#include "ft_printf.h"

#include <stdio.h>
int main(void)
{
	printf("%d\n", ft_printf("%d\n", 9223372036854775807LL));
	printf("%d\n", printf("%d\n", 9223372036854775807LL));
}