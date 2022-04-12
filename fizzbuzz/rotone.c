#include <unistd.h>

int ft_strlen(char	*str)
{
return (0);
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
	char	*str = argv[1];
	char	*res;
	char	c;
	while (*str)
	{
		if (*str == 'z')
		{
			write(1, "a", 1);
			str++;
			break;
		}
		if (*str == 'Z')
		{
			write(1, "A", 1);
			str++;
			break;
		}
		c = *(str)++;
		str++;
		write(1, &c, 1);

	}
	}
}
