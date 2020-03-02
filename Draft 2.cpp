#include <iostream>
#include <stdlib.h>
#include <sstream>
using namespace std;

double diff(double a, double b) {
	return a - b;
}


/*Given a pattern of numbers:
   - function converts pattern to a repeating decimal 
   - it then finds the corresponding fraction for the repeating decimal
   
   NOTE: 
    - THIS ONLY WORKS FOR REPEATING DECIMALS THAT ARE BETWEEN 0 AND 1!
   */
int* decToFrac(string pattern) {
	
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
			if ((diff(decimal, frac) <= 0.00001) and (diff(decimal, frac) > 0)) {
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

	string number, pattern = "";
	int decimal_index;
	int* frac;

	cout << "Enter a repeating decimal between 0 and 1 " << endl;
	cin >> number;

	try {
		// Find index of "."
		for (int i = 0; i < number.length(); i++) {
			if (number[i] == '.') {
				decimal_index = number[i];
				pattern = number.substr(i + 1);
				break;
			}
		}

		if (pattern == "") 
			// this will only happen 
			// when the string is not a decimal
			throw pattern;
	}
	catch (string pattern) {
		cout << "Error has been caught" << endl;
		return 0;
	}

	frac = decToFrac(pattern);
	cout << frac[0] << "/" << frac[1] << endl;
	return 0;
}
