#include <iostream>
#include <string>
#include <sstream>
#include <float.h>
#include <iomanip>
using namespace std;

long int* simplify(long int numerator, long int denominator) {

	/* - Check if each number from 1-100 is divisible by both numerator and denominator
		 - if so -> divide by that number
	   - repeat until there are no numbers from 1-100 which is divisible by both numerator and denominator */

	long int top = numerator;
	long int bottom = denominator;

	for (int num = 2; num < 1000; num++) {

		// debug line 
		cout << "Looking at num = " << num << endl;
		cout << "fmod(top, num) = " << fmod(top, num) << endl;  
		cout << "fmod(bottom, num) = " << fmod(bottom, num) << endl;  
		cout << "top / num: " << top / num << endl;
		cout << "bottom / num: " << bottom / num << endl;
		// end debug lines 

		if ((fmod(top, num) == 0) && (fmod(bottom, num) == 0)) {
			cout << "Simplifying by: " << num << endl; // debug line 

			top /= num;
			bottom /= num;
			num = 2;  // resets the loop 
		}

		// debug lines
		cout << "current fraction: " << top << "/" << bottom << endl;  
		cout << endl;
	}

	long int simplified_fraction[] = { top, bottom };
	return simplified_fraction;
}


std::string fractions(std::string decimal) {

	/*Two scenarios:
	   - decimal part of # is fully repeating
	   - decimal part is partially repeating */
	int parenthesis = 0, period = 0;
	string repeat, non_repeat, repeat_denominator;
	long int repeat_top, repeat_bottom, non_repeat_top, non_repeat_bottom;

	for (int i = 0; i < decimal.length(); i++) {
		if (decimal[i] == '(') { parenthesis = i; }
		if (decimal[i] == '.') { period = i; }

		/*DECIMAL PART IS WHOLLY REPEATING */
		if (period == parenthesis - 1) {

			// Get non repeating part of decimal 
			for (int j = 0; j < decimal.length(); j++) {
				if (decimal[j] == decimal[period]) { break; }
				non_repeat += decimal[j];
			}

			// Get repeating part of decimal 
			for (int j = period + 1; j < decimal.length(); j++) {
				if (decimal[j] == '(' or decimal[j] == ')') {
					continue;
				}

				repeat += decimal[j];
			}

			/*fraction: repeat / repeat.length() amount of 9's*/
			for (int j = 0; j < repeat.length(); j++) {
				repeat_denominator += "9";
			}

			// convert repeat and repeat_denominator to int and put it into an array 
			stringstream top(repeat); top >> repeat_top;
			stringstream bottom(repeat_denominator); bottom >> repeat_bottom;
			long int repeat_fraction[2] = { repeat_top, repeat_bottom };

			// conver non_repeat to int, then change non_repeat to fraction with repeat_bottom as denominator
			non_repeat_top = stoi(non_repeat); non_repeat_bottom = repeat_bottom;
			long int non_repeat_fraction[2] = { non_repeat_top * non_repeat_bottom , non_repeat_bottom };

			// add non_repeat_fraction and repeat_fraction, and simplify it after 
			long int fraction[2] = { repeat_fraction[0] + non_repeat_fraction[0], repeat_fraction[1] };

			// debug lines 
			cout << setprecision(20) << fraction[0] << "/" << setprecision(20) << fraction[1] << endl;
			cout << fraction[0] << "/" << fraction[1] << endl;


			// simply fraction and convert it to string 
			long int* simplified = simplify(fraction[0], fraction[1]);
			long int temp_array[2] = { simplified[0], simplified[1] };

			string numerator = to_string(temp_array[0]);
			string denominator = to_string(temp_array[1]);

			return numerator + "/" + denominator;
		}
	}


	/* DECIMAL PART IS PARTIALLY REPEATING */

	return "partially repeating decimal ";
}

int main() {

	cout << fractions("0.(052631578947368421)") << endl;
	return 0;
}


/* NOTES: 
- use long int 
- use strstr() and strtol() to get index of "(" and "."

"Again, whenever you're writing algorithms it is 
always good to write and test your ideas on the python terminal. 
It's easier to convert it to C++ code after that. Directly writing C/C++ code 
(if you're inexperienced) is not a good idea since you'll spend a large part 
of the work in debugging your code."


*/
