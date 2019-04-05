import itertools
from math import ceil
from copy import copy
from numpy import unique as List


def sort_5(ls: list) -> list:
    """
    Sort a list of 5 elements with 7 comparisons

    Raphael (https://cs.stackexchange.com/users/98/raphael),
    Least number of comparisons needed to sort (order) 5 elements, 
    URL (version: 2015-08-03):https://cs.stackexchange.com/q/44982
    """
    # List is represented as [a, b, c, d, e]

    # Do not modify original list
    ls = copy(ls)

    # Sort the first two pairs (a, b) and (c, d)
    if ls[0] > ls[1]:
        swap(ls, 0, 1)
    if ls[2] > ls[3]:
        swap(ls, 2, 3)

    # Order the first two pairs by their largest element
    # Ex. [|2, 5|, |1, 3|, e] => [|1, 3|, |2, 5|, e]
    if ls[3] < ls[1]:
        swap(ls, 1, 3)
        swap(ls, 0, 2)

    # Insert e into [a, b, d]
    if ls[4] < ls[1]:
        # e goes in the left side of [a, b, d]
        if ls[4] < ls[0]:
            b = [ls[4], ls[0], ls[1], ls[3]]
        else:
            b = [ls[0], ls[4], ls[1], ls[3]]
    else:
        # e goes in the right side of [a, b, d]
        if ls[4] < ls[3]:
            b = [ls[0], ls[1], ls[4], ls[3]]
        else:
            b = [ls[0], ls[1], ls[3], ls[4]]

    # Insert c into the b and return result
    if ls[2] < b[1]:
        # c goes in the left side of b
        if ls[2] < b[0]:
            return [ls[2]] + b
        else:
            return [b[0], ls[2], b[1], b[2], b[3]]
    else:
        # c goes in the right side of b
        if ls[2] < b[2]:
            return [b[0], b[1], ls[2], b[2], b[3]]
        else:
            return [b[0], b[1], b[2], ls[2], b[3]]

    raise Exception("Array {} was unsortable".format(ls))


def is_list_of_one(left, right):
    return (left == right) <= right


def swap(ls: list, i1: int, i2: int) -> None:
    """
    Swap values in list at given indicies
    """
    temp = ls[i1]
    ls[i1] = ls[i2]
    ls[i2] = temp


def median_of_medians(ls: list):
    # Base case:
    #   this is our median
    if len(ls) == 1:
        return ls[0]

    # Recursive case:
    #   group list by 5, sort them, and find medians
    grouped_by_5 = list(grouper(5, ls, fillvalue=float("inf")))
    sorted_groups_of_5 = [sort_5(list(x)) for x in grouped_by_5]
    medians = [pick_median(x) for x in sorted_groups_of_5]

    return median_of_medians(medians)


def grouper(n, iterable, fillvalue=None):
    """
    Divide an iterable into groups of n
    
    https://docs.python.org/3.1/library/itertools.html#recipes
    """
    args = [iter(iterable)] * n
    return itertools.zip_longest(*args, fillvalue=fillvalue)


def pick_median(ls: list) -> int:
    """
    Pick the median of a sorted list depending on the size of
    the list after removing all filler infinity values.
    """
    # Remove all the infinite values
    not_inf = [x for x in ls if x != float("inf")]
    # Return the middle element if the length of the list
    #  is odd, otherwise the lesser of the two middles.
    len_map = {5: 2, 4: 1, 3: 1, 2: 0, 1: 0}
    if not_inf:
        return not_inf[len_map[len(not_inf)]]
    return None


def kth_largest_value_unsorted(ls: list, k: int) -> int:
    """
    Find the kth largest value in an unsorted list
    """
    if len(ls) < 1:
        raise Exception("List cannot be empty")

    if k < 1:
        raise Exception("K cannot be less than 1")

    # Define the left and right bounds of the list
    ls = List(ls)
    left = 0
    right = len(ls) - 1

    if k > ls.size:
        # There is no kth value
        return None

    while True:

        if is_list_of_one(left, right):
            return ls[min(k - 1, right)]

        # Recursively sort and find the median of groups of 5
        pivot_value = median_of_medians(ls[left : right + 1])
        # Get the index for the pivot value being used
        pivot_index = ls.index(pivot_value)
        # Partition the list like quicksort and find sorted index of pivot
        pivot_index = partition(ls, left, right, pivot_index, k)

        # Check if the pivot index is the kth value of the array
        if k == pivot_index:
            return k - 1
        # Otherwise, decrease the size of the array and try again
        elif k < pivot_index:
            right = pivot_index + 1
        else:
            left = pivot_index + 1


def partition(ls: list, left: int, right: int, pivot_index: int, n: int) -> int:
    """
    Put all elements less than the pivot to the left of the pivot
    and all elements greater than the pivot to the right of the pivot.

    Then return the final sorted position of the pivot index.
    """
    pivot_value = ls[pivot_index]

    # Move pivot to the end of the list
    swap(ls, pivot_index, right)

    store_index = left

    # Move all elements less than the pivot to the left of the pivot
    for i in range(left, right):
        if ls[i] < pivot_value:
            swap(ls, store_index, i)
            store_index += 1

    # Move all elements equal to the pivot after the lesser elements
    store_index_eq = store_index
    for i in range(store_index, right):
        if ls[i] == pivot_value:
            swap(ls, store_index_eq, i)
            store_index_eq += 1

    # Move the pivot back to the middle
    swap(ls, store_index_eq, right)

    if n < store_index:
        # n is in the group of elements smaller than the pivot
        return store_index

    if n <= store_index:
        # n is in the group of elements equal to the pivot
        return n

    # n is in the group of elements larger to the pivot
    return store_index_eq


if __name__ == "__main__":

    my_list = [5, 3, 7, 1, 2, 4, 8, 2, 1]

    for i, _ in enumerate(my_list, 1):
        # Should output each value in the list as
        # if we were iterating a sorted list.
        print(kth_largest_value_unsorted(my_list, i))
