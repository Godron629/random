
import unittest
from math import floor, e
from io import StringIO


# Derangement code golf: see `derangement` definition.
# `(n-1)*-1` Is the base case, converting 0 to 1 and 1 to 0.
#    This was used as elif cannot be used and double lambda is lame.
d = lambda n: (n-1)*-1 if n in [0,1] else n*(d(n-1)) + (-1)**n


def derangement(n: int) -> int:
    '''
    Calculate derangement of a number.

    I.e. the number of permutations of n where no element appears
    in its original position.

    https://en.wikipedia.org/wiki/Derangement
    '''
    if n < 0:
        raise ValueError('Derangement only defined for n > -1')
    if n == 0:
        return 1
    if n == 1:
        return 0
    return nearest_integer(factorial(n) / e)

def nearest_integer(n: float) -> int:
    '''
    Return the nearest integer of n
    '''
    return int(floor(n + 0.5 ))

def factorial(n: int) -> int:
    '''
    Return factorial (n!) of n
    '''
    if n < 0:
        raise ValueError('Factorial only defined for n > -1')
    if n in [0, 1]:
        return 1
    return n * factorial(n - 1)


class TestDerangement(unittest.TestCase):

    def test_normal_integer(self):
        self.assertEqual(265, derangement(6))

    def test_base_case_one_returns_zero(self):
        self.assertEqual(0, derangement(1))

    def test_base_case_zero_returns_one(self):
        self.assertEqual(1, derangement(0))

    def test_negative_raises_valueerror(self):
        with self.assertRaises(ValueError):
            derangement(-1)


if __name__ == '__main__':

    print("Running code golf...\n")
    for n in [0, 1, 6, 9]:
        print(d(n))

    print("\nRunning `derangement` unit tests...\n")

    suite = unittest.TestSuite()

    test_cases = [
        'test_normal_integer',
        'test_base_case_one_returns_zero',
        'test_base_case_zero_returns_one',
        'test_negative_raises_valueerror',
    ]

    for t in test_cases:
        suite.addTest(TestDerangement(t))

    runner = unittest.TextTestRunner()
    runner.run(suite)

    print("\nReading challenge input...\n")

    # "You'll be given inputs as one integer per line."
    #  "Your program should yield the subfactorial result."
    #  Pff, files? What is this - 1995?
    challenge_input = '6\n9\n14\n'
    file = StringIO(challenge_input)
    for line in file:
        print(derangement(int(line)))
