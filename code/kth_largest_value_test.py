import os

from timeit import Timer
from kth_largest_value_sorted import kth_largest_value_sorted
from kth_largest_value_unsorted import kth_largest_value_unsorted


dir_path = os.path.dirname(os.path.realpath(__file__))


def small_test():
    """Here be a basic test that shows both algorithms work"""

    my_list = [5, 3, 7, 1, 2, 4, 8, 2, 1]

    print("\nSmall test: Kth largest value sorted:")
    print("This should print out the 1st to last value in `my_list`")
    for i, _ in enumerate(my_list, 1):
        # Should output each value in the list as
        # if we were iterating a sorted list.
        print("   {}".format(kth_largest_value_sorted(my_list, i)))

    print("\nSmall test: Kth largest value unsorted:")
    print("This should print out the 1st to last value in `my_list`")
    for i, _ in enumerate(my_list, 1):
        # Should output each value in the list as
        # if we were iterating a sorted list.
        print("   {}".format(kth_largest_value_unsorted(my_list, i)))


def bigger_test():
    """Here be a larger test where we pick the 50th element out of list of 100 integers"""

    my_list = []
    with open(os.path.join(dir_path, "list_of_integers.txt")) as f:
        for line in f.readlines():
            my_list.append(int(line.split("\n")[0]))
    
    # The 50th element also by chance happens to be 50! Wow!
    print("\nThe results of these two runs should be equivilent:")
    print("  Kth largest value unsorted:")
    print("  {}".format(kth_largest_value_unsorted(my_list, 50)))
    print("  Kth largest value sorted:")
    print("  {}".format(kth_largest_value_sorted(my_list, 50)))

if __name__ == "__main__":
    small_test()
    bigger_test()

