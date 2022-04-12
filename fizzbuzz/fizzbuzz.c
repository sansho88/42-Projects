#include <unistd.h>

void	putnbr(int nbr)
{

	if (nbr > 9)
		putnbr(nbr / 10);
	write(1, &nbr - '0', 1);
}

int main()
{
int	i = 0;

while (i <= 100)
	{
		if(i % 3 == 0 && i % 5 == 0)
			write(1, "fizzbuzz\n", 8 + 1);
		else if (i % 3 == 0 )
			write(1, "fizz\n", 4 + 1);
		else if (i % 5 == 0)
			write(1, "buzz\n", 4 + 1);
		else
			putnbr(i);
		write(1, "\n", 1);
		i++;
	}
}
