#include <iostream>
using namespace std;

/*Write a function that, given 2 non-zero numbers, find the GCD of those 2 numbers. 
  NOTE: num1 > num2 for this to work. */

int gcd(int num1, int num2) {

    // If num2 > num1, swap the variables 
	if (num2 > num1) {
		int temp = num1; 
		num1 = num2;
		num2 = temp;
	}

	int current_divisor = 1;

	if (num1 == 0)
		return num2;
	else if (num2 == 0)
		return num1;
	else {
		current_divisor = gcd(num2, num1 % num2);
	}
}


int main() {

	cout << gcd(42, 56) << endl;
	return 0;
}
