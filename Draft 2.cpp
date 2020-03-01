#include <iostream>
#include <stdlib.h>
using namespace std;

double diff(double a, double b) {
	return a - b;
}


/*Given a pattern of numbers:
   - function converts pattern to a repeating decimal 
   - it then finds the corresponding fraction for the repeating decimal
   
   NOTE: 
    - THIS ONLY WORKS FOR DECIMALS THAT ARE BETWEEN 0 AND 1!
   */
double decToFrac(string pattern) {
	
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

			// debug lines (remove later)
			cout << numerator << "/" << denominator << " in decimal form: " << frac << endl;
			cout << decimal << endl;

			// if the fraction equals decimal 
			if ((diff(decimal, frac) <= 0.00001) and (diff(decimal, frac) > 0)) {
				cout << "WE HAVE FOUND A MATCH!" << endl;
				fraction[0] = numerator;
				fraction[1] = denominator;
				cout << fraction[0] << "/" << fraction[1] << endl; // debug line 

				is_break = true;
				break;
			}
		}

		if (is_break == true)
			break;
	}



	return decimal;
}

int main() {

	cout << decToFrac("020408163265306122448979591836734693877551") << endl;
	return 0;
}
