import math 
""" Given a repeating decimal of the format: ###.(###) or ###.##(###), with repeating part of decimal
between (), function will return the simplified fraction corresponding to the decimal. """


# fraction parameter is a list
def simplify(nume, den):
    numerator = nume
    denominator = den

    """For loop checks every number (num) between 2-1000 to see if numerator and denominator 
    can both divide into it. If that is the case, numerator and denominator will divide by num
    and the loop will reset back to 2, repeating the process over again. """
    for num in range(2, 1001):
        print("numerator: {} \ndenominator: {} \nnum: {} ".format(int(numerator), int(denominator), num)) # debug statement
        print("numerator / num = {} \ndenominator / num = {}".format(int(numerator / num), int(denominator / num)))

        if (numerator % num == 0) and (denominator % num == 0):
            # debug statements
            print("Divisible by {}".format(num))

            numerator /= num
            denominator /= num

            print("numerator: {} \ndenominator: {} \nnum: {} ".format(int(numerator), int(denominator), num)) # debug statement

        print("\n") # buffer at end of loop

    simplified = [numerator, denominator]
    print(simplified)



def fractions(decimal_string):
    """ Two scenarios:
        - decimal part is fully repeating
        - decimal part is partially repeating """

    # find index of "(" and "." to see if fully or partially repeating
    parenthesis_index = decimal_string.index("(")
    period_index = decimal_string.index(".")

    if parenthesis_index == period_index + 1:
        # fraction is wholly repeating
        fully_repeat(decimal_string, parenthesis_index, period_index)
    else:
        partially_repeat(decimal_string, parenthesis_index, period_index)



# If fraction is fully repeating: ###.(####)
def fully_repeat(decimal_str, parenthesis, period):
    # Get non-repeating and repeating part of decimal
    non_repeat = decimal_str[:parenthesis - 1]
    repeat = decimal_str[parenthesis + 1: len(decimal_str) - 1]

    # turn repeat into a fraction
    # fraction: repeat / repeat.length() amount of 9's
    repeat_fraction = [int(repeat), int("9" * len(repeat))]

    """NOTE: use repeat_fraction[1] as the common denominator"""

    # turn non_repeat into a fraction
    non_repeat_fraction = [int(non_repeat) * repeat_fraction[1], repeat_fraction[1]]

    # add repeat_fraction and non_repeat fraction together
    fraction = [repeat_fraction[0] + non_repeat_fraction[0], repeat_fraction[1]]

    simplify(fraction[0], fraction[1])



# If fraction is partially repeating: ###.###(#####....)
def partially_repeat(decimal_str, parenthesis, period):
    pass


# -------------------- Main -----------------------------
print(fractions("0.(052631578947368421)"))
