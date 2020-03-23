#include <iostream>
#include <stdio.h>
#include <string.h>
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


string fully_repeat(char decimal_char[]) {
	/*NOTE: decimal_char is the decimal string in the form of a char array */

	// get repeating part
	char* temp1 = strstr(decimal_char, "(");
	string temp2 = temp1;
	string repeat_str = temp2.substr(1, temp2.length() - 2);

	// get non-repeating part
	string non_repeat_str;
	for (int i = 0; i < 30; i++) {
		if (decimal_char[i] == '.')
			break;
		non_repeat_str += decimal_char[i];
	}

	// Convert repeat and non_repeat into a long long int
	long long int repeat = stoll(repeat_str);
	long long int non_repeat = stoll(non_repeat_str);

	// turn repeat into a fraction
	// fraction: repeat / repeat.length() amount of 9's
	string repeat_denominator_str;
	for (int i = 0; i < repeat_str.length(); i++) repeat_denominator_str += "9";
	long long int fraction_repeat[2] = { repeat, stoll(repeat_denominator_str) };

	/* NOTE: USE fraction_repeat[1] as the denominator */

	// turn non_repeat into a fraction 
	long long int fraction_non_repeat[2] = { non_repeat * fraction_repeat[1], fraction_repeat[1]};

	// add repeat_fraction and non_repeat_fraction together 
	long long int fraction[2] = { fraction_repeat[0] + fraction_non_repeat[0], fraction_repeat[1]};

	// simplify the fraction 
	unsigned long long int* pTemp = simplify(fraction[0], fraction[1]);
	unsigned long long int return_fraction[2] = { pTemp[0], pTemp[1] };

	// convert return_fraction array to string, and return it 
	string numerator = to_string(return_fraction[0]);
	string denominator = to_string(return_fraction[1]);
	
	return numerator + "/" + denominator;
}


string partially_repeat(string decimal) {

	return "stub";
}


string fractions(string decimal) {
	// Convert decimal into a char array called decimal_char[]
	char decimal_char[30];
	strcpy_s(decimal_char, decimal.c_str());

	// find "(" and "." to see if fully or partially repeating
	char* decimal_part = strstr(decimal_char, ".");
	if (decimal_part[1] == '(') {
		// If the there is a parenthesis after the '.'
		return fully_repeat(decimal_char);
	}
	else {
		cout << "Partially Repeating Fraction" << endl;
		return "stub";
	}

}


int main() {
	/* Fully Repeating Test Case: 0.(052631578947368421) 
	   Partially Repeating Test Case: 1.017(857142) */

	cout << fractions("0.(052631578947368421)") << endl;

	return 0;
}
