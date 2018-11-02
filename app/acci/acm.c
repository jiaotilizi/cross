#include <stdio.h>

int factorial(int n, int * sum){
	return n && (*sum += n) && factorial(--n, sum);
}

int main(int argc, char * argv[]){
	int n = 10;
	int sum = 0;
	factorial(10, &sum);
	printf("Factorial of %d is %d.\n", n, sum);
}
