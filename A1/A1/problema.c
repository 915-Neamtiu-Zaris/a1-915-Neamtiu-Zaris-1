#include <stdio.h>

/*
1.
a. Generate all the prime numbers smaller than a given natural number n.
b. Given a vector of numbers, find the longest increasing contiguous subsequence,
such the sum of that any 2 consecutive elements is a prime number.

Write a C application with a menu based console interface which solves one of the problems below.
Menu entries are expected for reading a vector of numbers from the console,
solving each of the 2 required functionalities and exiting the program.
Each requirement must be resolved using at least one function.
Functions communicate via input/output parameters and the return statement.
Provide specifications for all functions.
due in week 2.
*/

void print_menu();
void sieve_of_erathostenes(int n);
int prime(int n);
void subseq(int n, int arr[], int* start, int* length);

int main()
{
	print_menu();

	// Getting user input for option.
	int option;
	printf("\nOption: ");
	scanf_s("%d", &option);
	//

	if (option == 1)
	{
		// If the option is 1, then print all prime numbers smaller than a given n.
		// using Sieve of Erathosthenes

		int n;
		printf("n: ");
		scanf_s("%d", &n);

		sieve_of_erathostenes(n);
	}
	else
	{
		// If the option is 2...

		// Ask for length of the array
		int n;
		printf("Length of array: ");
		scanf_s("%d", &n);

		// Read array
		printf("Elements of array: ");
		int arr[1001];
		for (int i = 1; i <= n; ++i)
			scanf_s("%d", &arr[i]);

		int start = 0;
		int length = 0;
		subseq(n, arr, &start, &length);

		// Printing the subsequence
		for (int i = start; i < start + length; ++i)
			printf("%d ", arr[i]);
	}

	return 0;
}

void print_menu()
{
	printf("1 - Generate all the prime numbers smaller than a given natural number n.\n2 - Given a vector of numbers, find the longest increasing contiguous subsequence, such the sum of that any 2 consecutive elements is a prime number.");
}

void sieve_of_erathostenes(int n)
{
	/* 
	Creates an array of booleans. At the end of the algorithm, on each position i of the array there will be
	a value of 1 if the integer i is not prime, 0 otherwise.

	n - size of the array
	*/

	int prime[10001] = { 0 };

	int p = 2;

	while (p * p <= n)
	{
		// For each prime number, go through all multiples that are greater than the square of the number
		// and mark it as non prime. At the end, the prime numbers will remain unmarked.
		if (prime[p] == 0)
			for (int i = p * p; i <= n; i += p)
				prime[i] = 1;

		p += 1;
	}
	
	// Printing the prime numbers
	for (int i = 1; i <= n; ++i)
		if (prime[i] == 0)
			printf("%d ", i);

	return;
}

int prime(int n)
{
	// Returns 1 if n is prime, 0 otherwise

	if (n < 2)
		return 0;

	if (n == 2)
		return 1;

	if (n % 2 == 0)
		return 0;

	for (int d = 3; d * d <= n; d += 2)
		if (n % d == 0)
			return 0;

	return 1;
}

void subseq(int n, int arr[], int* start, int* length)
{
	// Receives an array and its length.
	// Returns the start index and the length of the longest increasing contiguous subsequence of the array,
	// such that the sum of any 2 consecutive numbers is prime, through the arguments passed by reference: "start" and "length".

	int current_l = 0; // current length
	int max_l = -1; // max length
	int current_start = 0; // start index
	int max_start = 0; // max seq start index
	
	int j;

	// Parse the array
	for (int i = 1; i < n; ++i)
	{
		// If the sum of the current element and the next one is prime,
		// and they are ordered increasingly, we have found a potential subsequence.
		if (prime(arr[i] + arr[i + 1]) == 1 && arr[i] <= arr[i + 1])
		{
			j = i + 1;
			current_l = 2;
			current_start = i;

			// Keep going until we reach the end of the current subsequence.
			while (prime(arr[j] + arr[j + 1]) == 1 && arr[j] <= arr[j + 1] && j + 1 <= n)
			{
				j++;
				current_l++;
			}

			i = j;

			// After finding the total length of the current subseq, compare it to the max susbeq.
			if (current_l > max_l)
			{
				max_l = current_l;
				max_start = current_start;
			}
		}
	}

	*start = max_start;
	*length = max_l;

	return;
}