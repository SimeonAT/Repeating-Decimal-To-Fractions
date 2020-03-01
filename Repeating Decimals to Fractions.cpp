#include <iostream>
#include <typeinfo>
using namespace std;

int* decToFrac(string num) {  // Function that turns a decimal (in form of a string) into an unsimplified fraction 

    int numerator, denominator;

    // convert num into float 
    double decimal = ::atof(num.c_str());

    // convert decimal into an unsimplified fraction 
    int counter = 1;
    while (floor(decimal) != decimal) {
        decimal *= 10;
        counter *= 10;
    } // fraction is decimal/counter 

    numerator = decimal; denominator = counter;
    int fraction[2] = { numerator, denominator };


    /*Returns a pointer to array called fraction:
    fraction[0]: numerator
    fraction[1]: denominator */
    return fraction;
}

void repeatingDecToFrac(string num) { // converts repeating decimal into an unsimplified fraction 

    int numerator, denominator; 
    
    // convert num into float 
    double decimal = ::atof(num.c_str());


}


int* addFrac(int* repeat, int* non_repeat) {
 
    int numerator = (repeat[0] * non_repeat[1]) + (non_repeat[0] * repeat[1]);
    int denominator = repeat[1] * non_repeat[1];

    int fraction[2] {numerator, denominator};

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

    int simplified_fraction[] = {top, bottom};
    return simplified_fraction;
}


std::string fractions(std::string decimal) {

    /* split the string into two substrings:
      one holds the whole number part 
     the other holds the repeating part */

    string decimal2 = decimal.substr(0, decimal.length() - 1); // decimal2 is decimal without the enclosing ")"
    
    string non_repeat, repeat;
    string substr1, substr2, substr3;
    int period_index, parenthesis_index = 0; // holds index location for '.' and '(' character 

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

    cout << "non_repeat: " << non_repeat << endl;
    cout << "repeat: " << repeat << endl;

    // convert repeat into a repeating fraction 

    return "stub";

}

int main()
{
    
    string input;
    cout << "Enter a decimal (with parenthesis) : " << endl;
    cin >> input;
    
    string temp = fractions(input);

    return 0;
}


