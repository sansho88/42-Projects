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
		numbers[i - 1] = ft_atoi(argv[i]);
		i++;
	}
	return (numbers);
}
/////////////RADIX C+- Version ////////

// A utility function to get maximum value in arr[]
int getMax(int arr[], int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return (mx);
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void	countSort(int arr[], int n, int exp)
{
	int output[n]; // output array
	int i, count[10] = { 0 };

	// Store count of occurrences in count[]
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	// Change count[i] so that count[i] now contains actual
	// position of this digit in output[]
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Build the output array
	for (i = n - 1; i >= 0; i--) {
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	// Copy the output array to arr[], so that arr[] now
	// contains sorted numbers according to current digit
	for (i = 0; i < n; i++)
		arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using
// Radix Sort
void radix(int arr[], int n)
{
	// Find the maximum number to know number of digits
	int m;
	int exp;

	m = getMax(arr, n);
	exp = 1;
	// Do counting sort for every digit. Note that instead
	// of passing digit number, exp is passed. exp is 10^i
	// where i is current digit number
	while (m / exp > 0)
	{
		countSort(arr, n, exp);
		exp *= 10;
	}
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

// Driver Code

# include <stdio.h>
int main()
{
	int arr[] = { 170, 45, 75, 90, 802, 24, 2, 66 };
	int n = sizeof(arr) / sizeof(arr[0]);

	// Function Call
	radix(arr, n);
	print(arr, n);
	return 0;
}

