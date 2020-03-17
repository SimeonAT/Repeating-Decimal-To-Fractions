#include <iostream>
#include <string>
#include <sstream>
#include <float.h>
#include <iomanip>
using namespace std;

void simplify(double numerator, double denominator) {

	/* Find GCD of top and bottom, and divide both top and bottom by that GCD */

	double top = numerator;
	double bottom = denominator;

	cout << top << "/" << bottom << endl;

}


std::string fractions(std::string decimal) {

	/*Two scenarios:
	   - decimal part of # is fully repeating
	   - decimal part is partially repeating */
	int parenthesis = 0, period = 0;
	string repeat, non_repeat, repeat_denominator;
	double repeat_top, repeat_bottom, non_repeat_top, non_repeat_bottom;

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
			double repeat_fraction[2] = { repeat_top, repeat_bottom };

			// conver non_repeat to int, then change non_repeat to fraction with repeat_bottom as denominator
			non_repeat_top = stoi(non_repeat); non_repeat_bottom = repeat_bottom;
			double non_repeat_fraction[2] = { non_repeat_top * non_repeat_bottom , non_repeat_bottom };

			// add non_repeat_fraction and repeat_fraction, and simplify it after 
			double fraction[2] = { repeat_fraction[0] + non_repeat_fraction[0], repeat_fraction[1] };

			// debug lines 
			cout << setprecision(20) << fraction[0] << "/" << setprecision(20) << fraction[1] << endl;


			// simply fraction and convert it to string 

		}
	}


	/* DECIMAL PART IS PARTIALLY REPEATING */

	return "partially repeating decimal ";
}

int main() {

	cout << fractions("0.(052631578947368421)") << endl;
	return 0;
}
