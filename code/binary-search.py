from typing import TypeVar
from math import floor, ceil

Number = TypeVar("Number", int, float)


def binary_search(ls: list, value: Number) -> int:
    """
    Binary search a sorted list for value

    Args: 
        ls: A list
        value: A number to search for 

    Returns: 
        int: Index of value if found otherwise -1
    """
    left = 0
    right = len(ls) - 1
    while left <= right:
        middle = floor((left + right) / 2)
        if ls[middle] < value:
            left = middle + 1
        elif ls[middle] > value:
            right = middle - 1
        else:
            return middle
    return -1


def binary_search_alt(ls: list, value: Number) -> int:
    """
    Alternate version of binary search where equality check
    is only performed when the length of the list is 1.

    Args: 
        ls: A list
        value: A number to search for 

    Returns: 
        int: Index of value if found otherwise -1
    """
    l = 0
    r = len(ls) - 1

    check = lambda x: not_found if ls[x] != value else x
    not_found = -1

    if not ls:
        return not_found

    if l >= r:
        check(l)

    while l != r:
        m = ceil((l + r) / 2)
        if ls[m] > value:
            r = m - 1
        else:
            l = m

    return check(l)


if __name__ == "__main__":
    print(binary_search([1, 2, 3, 4, 5], 5))
    print(binary_search_alt([1, 2, 3, 4, 5], 6))
    print(binary_search_alt([1], 1))
