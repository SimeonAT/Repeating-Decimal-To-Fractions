#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int* simplify(int numerator, int denominator) {

	/* - Check if each number from 1-100 is divisible by both numerator and denominator
		 - if so -> divide by that number
	   - repeat until there are no numbers from 1-100 which is divisible by both numerator and denominator */

	int top = numerator;
	int bottom = denominator;

	for (int num = 2; num < 1000; num++) {
		if ((top % num == 0) && (bottom % num == 0)) {
			top /= num;
			bottom /= num;
			num = 2;  // resets the loop 
		}
	}

	int simplified_fraction[] = { top, bottom };
	return simplified_fraction;
}


std::string fractions(std::string decimal) {
	
	/*Two scenarios:
	   - decimal part of # is fully repeating 
	   - decimal part is partially repeating */
	int parenthesis = 0, period = 0;
	string repeat, non_repeat, repeat_denominator;
	int repeat_top, repeat_bottom, non_repeat_top, non_repeat_bottom;

	for (int i = 0; i < decimal.length(); i++) {
		if (decimal[i] == '(') { parenthesis = i; }
		if (decimal[i] == '.') { period = i; }

		/*DECIMAL PART IS WHOLLY REPEATING */
		if (period == parenthesis - 1) {

			// Get non repeating part of decimal 
			for (int j = 0; j < decimal.length(); j++) {
				if (decimal[j] == decimal[period]) { break;  }
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
			repeat_top = stoi(repeat); 
			
			/*------------------- FIXME! OVERFLOW HERE ---------------------*/
			repeat_bottom = stoi(repeat_denominator); 
			/*--------------------------------------------------------------*/
			
			int repeat_fraction[2] = { repeat_top, repeat_bottom };

			// conver non_repeat to int, then change non_repeat to fraction with repeat_bottom as denominator
			non_repeat_top = stoi(non_repeat); non_repeat_bottom = repeat_bottom;
			int non_repeat_fraction[2] = {non_repeat_top * non_repeat_bottom , non_repeat_bottom};

			// add non_repeat_fraction and repeat_fraction, and simplify it after 
			int fraction[2] = {repeat_fraction[0] + non_repeat_fraction[0], repeat_fraction[1]};

			// simply fraction and convert it to string 
			int* simplified = simplify(fraction[0], fraction[1]);
			int temp_array[2] = {simplified[0], simplified[1]};

			string numerator = to_string(temp_array[0]);
			string denominator = to_string(temp_array[1]);

			return numerator + "/" + denominator;
		}
	}


	/* DECIMAL PART IS PARTIALLY REPEATING */

	return "partially repeating decimal ";
}

int main() {

	cout << fractions("1.(1)") << endl;
	return 0;
}
