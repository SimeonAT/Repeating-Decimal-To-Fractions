#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <string>
using namespace std;


unsigned long long int gcd(unsigned long long int num1, unsigned long long int num2) {

	// If num2 > num1, swap the variables 
	if (num2 > num1) {
		unsigned long long int temp = num1;
		num1 = num2;
		num2 = temp;
	}

	unsigned long long int current_divisor = 1;

	if (num1 == 0)
		return num2;
	else if (num2 == 0)
		return num1;
	else {
		current_divisor = gcd(num2, num1 % num2);
	}
}

unsigned long long int* simplify(unsigned long long int nume, unsigned long long int den) {
	unsigned long long int numerator = nume;
	unsigned long long int denominator = den;

	// Find GCD, then divide numerator and denominator by GCD 
	unsigned long long int divisor = gcd(nume, den);
	numerator = numerator / divisor;
	denominator = denominator / divisor;

	unsigned long long int simplified[] = { numerator, denominator };
	return simplified;
}


string fully_repeat(string decimal) {
	// Convert decimal into a char array called decimal_char[]
	char decimal_char[1024];
	strcpy_s(decimal_char, decimal.c_str());

	// Get the non-repeating and repeating parts of decimal_char
	char* temp1 = strstr(decimal_char, "(");
	string temp2 = temp1;
	string repeat = temp2.substr(1, temp2.length() - 2);

	cout << repeat << endl;
	return "stub";
}


string partially_repeat(string decimal) {

	return "stub";
}


string fractions(string decimal) {
	// Convert decimal into a char array called decimal_char[]
	char decimal_char[1024];
	strcpy_s(decimal_char, decimal.c_str());

	// find "(" and "." to see if fully or partially repeating
	char* temp = strstr(decimal_char, ".");
	if (temp[1] == '(')
		cout << "Fully Repeating Decimal" << endl;
	else
		cout << "Partially Repeating Fraction" << endl;


	return "stub";
}

int main() {
	/* Fully Repeating Test Case: 0.(052631578947368421) 
	   Partially Repeating Test Case: 1.017(857142) */

	fully_repeat("0.(052631578947368421)");

	return 0;
}
