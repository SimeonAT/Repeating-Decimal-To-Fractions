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

int main() {

	int* test = decToFracNonRepeat("10.25");
	cout << test[0] << "/" << test[1] << endl;
	return 0;
}
