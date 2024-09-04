/**************************************************/
/*                                                */
/*  Lab 1 Starter file                            */
/*                                                */
/*  Name:Royston Ng                               */
/*  Student number: 157150186                     */
/*                                                */
/**************************************************/

/* remember to code these in an iterative only manner*/

//This function accepts an unsigned integer and calculates
//all factorials of value n
//It returns every factorial value

unsigned int factorial(unsigned int n) {
	unsigned int num = n; //number we will factorialize.
	if (n < 2)
	{
		num = 1;
	}
	else
	{
		for (unsigned int i = n - 1; i > 0; i--)
		{
			num *= i;
		}
	}

	return num;
}

// This function accepts a double as a base and unsigned int n
// and returns a double equalling the base to the power of n
double power(double base, unsigned int n) {
	double num = base; //holds the base value and is used hold the current exponential iteration
	if (n < 1)
	{
		num = 1;
	}
	else if (n == 1)
	{
		num = base;
	}
	else
	{
		for (unsigned int i = n; i > 1; i--)
		{
			num = num * base;
		}
	}

	return num;
}

//This function returns the result of the fibonacci sequence for
//n rounds.
//The function accepts an unsigned integer n that represents the number of
//rounds in the sequence.

unsigned int fibonacci(unsigned int n) {
	//unsigned ints lower, higher and result represent the current
	//numbers in the round's sequence
	//result is to be returned while higher and lower are the sum that make
	//up result.
	unsigned int lower = 0, higher = 1, result = 1;

	if (n < 1)
	{
		return 0;
	}
	else if (n < 2)
	{
		return 1;
	}
	for (unsigned int i = n; i > 1; i--)
	{
		result = lower + higher;
		lower = higher;
		higher = result;
	}

	return result;
}
