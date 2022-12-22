"""Module providing function multiply."""


def multiply(arg_a, arg_b):
    """multiply to numbers."""
    print("Will compute", arg_a, "times", arg_b)
    arg_c = 0
    for _ in range(0, arg_a):
        arg_c = arg_c + arg_b
    return arg_c
