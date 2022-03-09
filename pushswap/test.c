
#include "pushswap.h"

/**TODO:
 * 		- Créer les listes
 * 		- Parser les args: OK
 * 		- Cr2er les fonctions de tri
 * 		- Générer les listes par rapport aux args
 * 		- Trier (Radix?)
 *
 * @return
 */

bool	checkdouble(int array[])
{
	size_t	size;
	int		i;
	int		j;
	int		nbchecked;

	size = sizeof(array) / sizeof(array[0]);
	i = -1;
	while (++i < size)
	{
		nbchecked = array[i];
		j = -1;
		while (++j < size - i)
			if (array[j] == nbchecked)
				return (true);
	}
	return (false);
}

int	*parseargs(int argc, char **argv)
{
	int	*numbers;
	int	i;

	numbers = malloc(sizeof(int) * argc - 1);
	if (!numbers)
		exit(EXIT_FAILURE);
	i = 1;
	while (i <= argc)
	{
		if (!checkdouble(numbers))
			numbers[i - 1] = ft_atoi(argv[i]);
		else
			quitps(NULL, NULL, -1);
		i++;
	}
	return (numbers);
}
/////////////RADIX C+- Version ////////

// A utility function to get maximum value in arr[]
int getmax(int arr[], size_t n, int *pos)
{
	int	max;
	int	i;

	max = arr[0];
	i = -1;
	*pos = 0;
	while (++i < n)
	{
		if (arr[i] > max)
		{
			max = arr[i];
			*pos = i;
		}
	}
	return (max);
}

int	getmin(int *arr, size_t n, int *pos)
{
	int	min;

	min = arr[0];
	*pos = 0;
	while (--n > 0)
	{
		if (arr[n] < min) //TODO: arr[n] is NULL?
		{
			min = arr[n];
			*pos = (int)n;
		}
	}
	return (min);
}

// A function to do counting radixsort_a of arr[] according to
// the digit represented by exp.
void	countsort(int arr[], int sizearr, int exp)
{
	int	*output; // output array
	int	i;
	int	count[10];

	output = ft_calloc(sizearr, sizeof(int));
	// Store count of occurrences in count[]
	i = -1;
	while (++i < sizearr)
		count[(arr[i] / exp) % 10]++;

	// Change count[i] so that count[i] now contains actual
	// position of this digit in output[]
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Build the output array
	for (i = sizearr - 1; i >= 0; i--) {
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	// Copy the output array to arr[], so that arr[] now
	// contains sorted numbers according to current digit
	for (i = 0; i < sizearr; i++)
		arr[i] = output[i];
}

/*Algo de tri:
 * En se basant sur radix (unités, dizaines, centaines, ...):
 * Digit par digit, si le digit est dans le bon groupe en cours de tri (ex:
 * num=41, nums triés: 11, 31, 51), alors le push dans la pile de sauvegarde
 * de tri, sinon le push en bas de la pile.
 * Avant tout, vérifier le nombre de digits concernés pour éviter de tourner
 * à l'infini.
 *
 * */
void	radixsort_a(t_stack *stacka, t_stack *stackb, int digit)
{
	int		i;
	int		exp;
	size_t	numbersconcerned;

	i = -1;
	exp = 1;
	/*while (++i < stacka->size)
	{*/
		numbersconcerned = countnmbrsconcerned(stacka->arr, stacka->size, digit,
				exp);
		while (numbersconcerned-- > 0)
		{
			if (stacka->arr[0] % 10 == digit)
				push_b(stacka->arr, &stacka->size, stackb->arr, &stackb->size);
			else
				rotate_a(stacka->arr, stacka->size);
		}
		exp *= 10;
	//}
}

void	radixsort_b(t_stack *stacka, t_stack *stackb, int digit)
{
	int		i;
	int		exp;
	size_t	numbersconcerned;

	i = -1;
	exp = 1;
	/*while (++i < stackb->size)
	{*/
		numbersconcerned = countnmbrsconcerned(stackb->arr, stackb->size, digit,
				exp);
		while (numbersconcerned-- > 0)
		{
			if (stackb->arr[0] % 10 == digit)
				push_a(stacka->arr, &stacka->size, stackb->arr, &stackb->size);
			else
				rotate_b(stackb->arr, stackb->size);
		}
		exp *= 10;
	//}
}

size_t	countnmbrsconcerned(int *arr, size_t size, int digit, int exp)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < size)
		if (arr[i] % 10 == digit)
			count++;
	return (count);
}

// A utility function to print an array
void print(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		ft_putnbr_fd(arr[i], 1);
		ft_putstr_fd(" ", 1);
	}
}

// The main function to that sorts arr[] of size arrsize using
// Radix Sort
/*void	radix(t_stack_a *stacka, t_stack_b *stackb)
{
	// Find the maximum number to know number of digits
	int	m;
	int	exp;
	int	digit;

	m = getmax(stacka->arr, stacka->size);
	exp = 1;
	digit = -1;
	// Do counting sort_a for every digit. Note that instead
	// of passing digit number, exp is passed. exp is 10^i
	// where i is current digit number
	while (++digit <= 9)
	{
		printf("digit = %d\n", digit);
		while (m / exp > 0)
		{
			//countsort(arr, arrsize, exp);
			//countnmbrsconcerned(arr, arrsize, digit++, exp);
			radixsort_a(stacka, stackb, digit);
			exp *= 10;
		}
		exp = 1;
		print(stacka->arr, stacka->size);
		puts("");
		while (m / exp > 0)
		{
			//countsort(arr, arrsize, exp);
			//countnmbrsconcerned(arr, arrsize, digit++, exp);
			radixsort_b(stacka, stackb, digit);
			exp *= 10;
		}
		print(stackb->arr, stackb->size);
		puts("");
	}
}*/

void	set_stacks(t_stack *stack_a, t_stack *stack_b)
{
	/*stack_a->size = sizeof(stack_a->arr) / sizeof(int);
	printf("Size of stackawsh = %zu\n", stack_a->size);
	stack_b->size = sizeof(stack_b->arr) / sizeof(int);*/
	if (stack_a->size > 0)
	{
		stack_a->min = getmin(stack_a->arr, stack_a->size, &stack_a->posmin);
		stack_a->max = getmax(stack_a->arr, stack_a->size, &stack_a->posmax);
	}
	if (stack_b->size > 0)
	{
		stack_b->min = getmin(stack_b->arr, stack_b->size, &stack_b->posmin);
		stack_b->max = getmax(stack_b->arr, stack_b->size, &stack_b->posmax);
	}
}

/**
 * Trier en divisant virtuellement la pile en 2. Envoyer chaque plus petit
 * dans la tack b, en fonction de si il est avant ou apres la moitié de la pile
 * @param stack_a
 * @param stack_b
 */
void	sort_stacks(t_stack *stack_a, t_stack *stack_b)
{
	set_stacks(stack_a, stack_b);
	printf("Size of stack a= %zu | min = %d\n", stack_a->size, stack_a->min);
	print(stack_a->arr, stack_a->size);
	if (stack_a->posmin >= stack_a->size / 2)
	{
		while (stack_a->arr[0] != stack_a->min)
			rotate_a(stack_a->arr, stack_a->size);
	}
	else if (stack_a->posmin < stack_a->size / 2)
	{
		while (stack_a->arr[0] != stack_a->min)
			reverse_rotate_a(stack_a->arr, stack_a->size);
	}
	push_b(stack_a->arr, &stack_a->size, stack_b->arr, &stack_b->size);
}

bool	isSorted(t_stack stacka, t_stack stackb)
{
	int	i;

	i = -1;
	if (stackb.size > 0)
		return (false);
	while (++i < stacka.size - 1)
		if (stacka.arr[i] > stacka.arr[i + 1])
			return (false);
	return (true);
}

// Driver Code
# include <stdio.h>
int main()
{
	int arr[] = { 170, 45, 75, 90, 802, 24, 2, 66 };
	int n = sizeof(arr) / sizeof(arr[0]);
	printf("sizeof wshwsh n= %d\n", n);
	t_stack	stacka;
	t_stack	stackb;

	stacka.arr = arr;
	stacka.size = n;
	stackb.arr = ft_calloc(sizeof(int), stacka.size);
	stackb.size = stacka.size;
	// Function Call
	while (stacka.size > 0)//(!isSorted(stacka, stackb))
		sort_stacks(&stacka, &stackb);
		//radix(&stacka, &stackb);
	puts("Result:");
	print(stacka.arr, stacka.size);
	dprintf(1, "\nStack b (si elle est pas vide:oupsi...): ");
	print(stackb.arr, stackb.size);
	return (0);
}

