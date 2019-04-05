def kth_largest_value_sorted(ls: list, k: int) -> int:
    """
    Return the kth largest value in a list that we sort
    """
    if k < 1:
        raise Exception("K cannot be less than 1")

    if not ls:
        raise Exception("List cannot be empty")

    new_list = []

    # Get rid of repeat values
    for i in ls:
        if i not in new_list:
            new_list.append(i)

    new_list.sort()

    if k > len(new_list):
        # There is no kth value in the list
        return None

    return new_list[k - 1]


if __name__ == "__main__":

    my_list = [5, 3, 7, 1, 2, 4, 8, 2, 1]

    for i, _ in enumerate(my_list, 1):
        # Should output each value in the list as
        # if we were iterating a sorted list.
        print(kth_largest_value_sorted(my_list, i))
