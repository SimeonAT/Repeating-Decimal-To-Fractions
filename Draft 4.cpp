#include <iostream>
#include <stdlib.h>
#include <sstream>
using namespace std;


/*---------------------------------------------------------------------------------------------*/

int* addFrac(int* repeat, int* non_repeat) {

	int numerator = (repeat[0] * non_repeat[1]) + (non_repeat[0] * repeat[1]);
	int denominator = repeat[1] * non_repeat[1];

	int fraction[2]{ numerator, denominator };

	return fraction;
}

int* simplify(int numerator, int denominator) {

	/* - Check if each number from 1-100 is divisible by both numerator and denominator
		 - if so -> divide by that number
	   - repeat until there are no numbers from 1-100 which is divisible by both numerator and denominator */

	int top = numerator;
	int bottom = denominator;

	for (int num = 2; num < 10000; num++) {
		if ((top % num == 0) && (bottom % num == 0)) {
			top /= num;
			bottom /= num;
		}
	}

	cout << "simplified fraction: " << top << "/" << bottom << endl;

	int simplified_fraction[] = { top, bottom };
	return simplified_fraction;
}

/*---------------------------------------------------------------------------------------------*/


double diff(double a, double b) {
	return a - b;
}


/*Return a rational decimal in the form of a fraction*/
int* decToFracNonRepeat(string num) {

	int whole_num = 0;
	int fraction[2];

	// convert string num into a double 
	double decimal = ::atof(num.c_str());

	// If there is whole number, find what the whole number is 
	for (double i = 0; i <= 1000000; i++) {
		if (floor(decimal) == i) {
			whole_num = i;
			break;
		}
	}

	// Compare decimal to fraction in existance 
	// To find its fractional form 
	int max_denominator;

	for (double denominator = 1; denominator <= 100; denominator++) {
		bool is_break = false; // did the outer loop break yet?

		// Makes dem large enough for fraction to be bigger than decimal 
		int max_numerator = denominator + (denominator * whole_num);

		for (double numerator = 0; numerator <= max_numerator; numerator++) {

			if (decimal == (numerator / denominator)) {
				fraction[0] = numerator; fraction[1] = denominator;
				is_break = true;
				break;
			}
		}
		if (is_break == true)
			break;
	}

	return fraction;

}



/*Given a pattern of numbers:
   - function converts pattern to a repeating decimal
   - it then finds the corresponding fraction for the repeating decimal

   NOTE:
	- THIS ONLY WORKS FOR REPEATING DECIMALS THAT ARE BETWEEN 0 AND 1!
   */
int* decToFracRepeat(string pattern) {

	// Convert pattern into a repeating decimal with 7 digits 
	string num_str = "0.";

	/*- Produce num_str of 6 sig figs
	  - Convert num_str from string to integer
	  - Round it down to 5 sig figs */
	while (true) {
		num_str += pattern.substr();
		if (num_str.length() > 8)
			break;
	}

	double decimal = atof(num_str.c_str()); // convert decimal into a double 


	int fraction[2]; // 0 -> numerator, 1 -> denominator 

	/*Find the corresponding fraction for decimal
	 I am going to do this by comparing every fraction in existance to decimal
	 until fraction == decimal */
	for (double denominator = 1; denominator <= INT_MAX; denominator++) {

		bool is_break = false; // did the inner loop break or not?

		for (double numerator = 0; numerator <= denominator; numerator++) {

			/*NOTE: frac != decimal because it seems frac as repeating while decimal as terminating.
			We may need to round frac to 7 digits before comparing whether frac is equal to decimal */
			double temp = (numerator / denominator) / 1000000;
			double frac = (numerator / denominator) - temp;

			// if the fraction equals decimal 
			if ((diff(decimal, frac) <= 0.000001) and (diff(decimal, frac) > 0)) {
				fraction[0] = numerator;
				fraction[1] = denominator;

				is_break = true;
				break;
			}
		}

		if (is_break == true)
			break;
	}



	return fraction;
}

std::string fractions(std::string decimal) {

	/* split the string into two substrings:
	  one holds the whole number part
	 the other holds the repeating part */

	string decimal2 = decimal.substr(0, decimal.length() - 1); // decimal2 is decimal without the enclosing ")"

	string non_repeat, repeat;
	string substr1, substr2, substr3;
	int period_index = 0, parenthesis_index = 0; // holds index location for '.' and '(' character 

	for (int i = 0; i < decimal2.length(); i++) {

		// Change repeat into a decimal with corect decimal place
		if (decimal2[i] == '.') {
			substr1 = decimal2.substr(i + 1);
			period_index = i;
		}

		if (decimal2[i] == '(') {
			parenthesis_index = i;

			substr2 = decimal2.substr(period_index + 1, parenthesis_index - period_index - 1);

			//substr3 
			substr3 = decimal2.substr(parenthesis_index + 1);

			// add substr2.length() zeros into repeat 
			repeat += ".";
			for (int p = 0; p < substr2.length(); p++) {
				repeat += "0";
			}

			// add substr3 into repeat 
			repeat += substr3;

			non_repeat = decimal2.substr(0, i);
			// add zero to end of non_repeat if "." is last character
			if (non_repeat.back() == '.') { non_repeat += "0"; }
		}
	}

	// convert repeat and non_repeat into fractions 
	int* temp_1 = decToFracNonRepeat(non_repeat);
	int non_repeat_fraction[] = {temp_1[0], temp_1[1]};

	/*BUG IN REPEAT FRACTION FUNCTION! FIX LATER! */
	int* temp_2 = decToFracRepeat(repeat.substr(1));
	int repeat_fraction[] = {temp_2[0], temp_2[1]}; 

	// Add fractions, simplify it, and return the result 
	int* temp = addFrac(non_repeat_fraction, repeat_fraction);
	int sum[] = {temp[0], temp[1]};
	int* temp3 = simplify(sum[0], sum[1]);
	int simplified_sum[] = {temp3[0], temp3[1]};

	cout << simplified_sum[0] << "/" << simplified_sum[1] << endl;

	return "stub";

}

int main() {

	string input;
	cout << "Enter a decimal (with parenthesis) : " << endl;
	cin >> input;

	string temp = fractions(input);
	return 0;
}
