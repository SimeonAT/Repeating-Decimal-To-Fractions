import math 
""" Given a repeating decimal of the format: ###.(###) or ###.##(###), with repeating part of decimal
between (), function will return the simplified fraction corresponding to the decimal. """


# fraction parameter is a list
def simplify(fraction):
    pass


def fractions(decimal_string):
    """ Two scenarios:
        - decimal part is fully repeating
        - decimal part is partially repeating """

    # find index of "(" and "." to see if fully or partially repeating
    parenthesis_index = decimal_string.index("(")
    period_index = decimal_string.index(".")

    if parenthesis_index == period_index + 1:
        # fraction is wholly repeating
        print("Fully repeating")
        fully_repeat(decimal_string)
    else:
        print("Partially repeating")
        partially_repeat(decimal_string)



def fully_repeat(decimal_str):
    pass


def partially_repeat(decimal_str):
    pass


# -------------------- Main -----------------------------
fractions("")
