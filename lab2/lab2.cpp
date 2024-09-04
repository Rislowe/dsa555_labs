/**************************************************/
/*                                                */
/*  Lab 2 Starter file                            */
/*                                                */
/*  Name: Royston Ng                              */
/*  Student number: 157150186                     */
/*                                                */
/**************************************************/

/* remember to code these in an iterative only manner*/

// This is a recursive version of the factorial function
//it takes unsigned integer n and returns the factorial
//of n
unsigned int factorial (unsigned int n){
	if (n < 2)
	{
		return 1;
	}
	return n * factorial(n - 1);	//n is multiplied with the same function passing
									//n-1 as the unsigned int for the next round
}

//	T(n)	= 1 + 3 + T(n-1)	--> if n < 2
//			= 4 + T(n-1)

//	T(0)	= 2

//	T(1)	= 2

//	T(2)	= 4 + 2
//	T(3)	= 4 + 4 + 2

//	T(n)	= 4(n-1) + 2
//			= 4n - 2

//Therefore T(n) is O(n)


//This is a recursive version of the power function
//It takes a double named base as the base number and an unsigned int n
//which represents the exponent.
//The function will return the value of base ^ n
double power (double base, unsigned int n){
	if (n == 0)								// 1
	{
		return 1;							// 1, if n == 0
	}

	if (n == 1)								// 1
	{
		return base;						// 1, if n == 1
	}

	return base * power(base, n - 1);		// 3 + T(n-1)


										//base is multiplied to function power using the same base,
										//but with n-1 as the exponent (AKA. the number of rounds to run the recursion)
}

//	T(n)	= 1 + 1 + 3 + T(n-1)	--> if n > 1
//			= 5 + T(n-1)
// 
//	T(0)	= 2
//	T(1)	= 2
// 
//	T(2)	= 5 + T(1)
//			= 5 + 2
// 
//	T(3)	= 5 + T(2)
//			= 5 + 5 + 2
// 
//	T(4)	= 5 + 5 + 5 + 2 
// 
//	The number of 5's is always 1 less than n, therefore:
// 
//	T(n)	= 5(n-1) + 2
//			= 5n - 3
// 
//	Therefore T(n) is O(n)
//	


//This is the recursive version of the Fibonacci function
//It takes an unsigned int n as the number of rounds to run the 
//Fibonacci sequence and returns the result.
unsigned int fibonacci (unsigned int n){
	if (n < 2)
	{
		return 2;
	}
	else
	{
		return fibonacci(n - 1) + fibonacci(n - 2);	//This time I am returning the sum of 2 recursively called fibonacci functions
													//This represents the previous 2 numbers in the sequence adding up to form
													//the next number in the sequence.
	}
}
