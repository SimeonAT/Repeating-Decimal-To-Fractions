import math 
""" Given a repeating decimal of the format: ###.(###) or ###.##(###), with repeating part of decimal
between (), function will return the simplified fraction corresponding to the decimal. """


# fraction parameter is a list
def simplify(nume, den):
    numerator = nume
    denominator = den

    """ Find GCD, then divide numerator and denominator by GCD """
    divisor = math.gcd(numerator, denominator)
    numerator /= divisor
    denominator /= divisor

    simplified = [numerator, denominator]
    return simplified



def fractions(decimal_string):
    """ Two scenarios:
        - decimal part is fully repeating
        - decimal part is partially repeating """

    # find index of "(" and "." to see if fully or partially repeating
    parenthesis_index = decimal_string.index("(")
    period_index = decimal_string.index(".")

    if parenthesis_index == period_index + 1:
        # fraction is wholly repeating
        return fully_repeat(decimal_string, parenthesis_index, period_index)
    else:
        return partially_repeat(decimal_string, parenthesis_index, period_index)



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

    return_fraction = simplify(fraction[0], fraction[1])

    return str(int(return_fraction[0])) + "/" + str(int(return_fraction[1]))



# If fraction is partially repeating: ###.###(#####....)
def partially_repeat(decimal_str, parenthesis, period):
    # Get non-repeating whole number, non-repeating decimal, repeating part of decimal
    non_repeat_whole = decimal_str[:period]
    non_repeat_decimal = decimal_str[period + 1: parenthesis]
    repeat = decimal_str[parenthesis + 1: len(decimal_str) - 1]

    """ Find out how many spot in the decimal places are not repeating;
        that is the power of 10 you need to divide it back to after converting into fraction """
    divide_back = len(non_repeat_decimal)

    # Assemble the "temporary" repeating decimal that
    # you're going to convert into a fraction
    temp_decimal = non_repeat_whole + non_repeat_decimal + ".(" + repeat + ")"

    """Everything is going to be done exactly the same as in the fully_repeat function. 
       The only catch is that you're gonna need to divide what you get by divide_back after doing so."""
    temp_string = fully_repeat(temp_decimal, temp_decimal.index("("), temp_decimal.index("."))
    slash_index = temp_string.index("/")
    temp_fraction = [int(temp_string[:slash_index]), int(temp_string[slash_index + 1:])]

    # divide by multiplying the denominator by divide_back
    temp_fraction[1] *= 10**divide_back

    # Simplify the fraction again
    return_fraction = simplify(temp_fraction[0], temp_fraction[1])

    return str(int(return_fraction[0])) + "/" + str(int(return_fraction[1]))


# -------------------- Main -----------------------------
print(fractions("1.017(857142)"))


# Test Cases
assert fractions("0.(09)") == "1/11"
assert fractions("0.0(45)") == "1/22"
assert fractions("2.1(313)") == "10646/4995"
assert fractions("0.0208(3)") == "1/48"
assert fractions("12.(12345)") == "404111/33333"
assert fractions("1.017(857142)") == "57/56"
assert fractions("0.(052631578947368421)") == "1/19"
