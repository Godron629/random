import string
from copy import deepcopy

def p1(file_name):
    with open(file_name) as f:
        heap = []
        while True:
            c = f.read(1)
            if c == '\n':
                break

            is_upper = c.isupper()

            opp_polar = c.upper() if c.islower() else c.lower()

            if not heap:
                heap.append(c)
            elif heap[-1] == opp_polar:
                heap.pop()
            else:
                heap.append(c)
    print(len(heap))


def p2(file_name):
    all_lower = string.ascii_lowercase
    all_upper = string.ascii_uppercase

    upper_then_lower = all_upper + all_lower
    lower_then_upper = all_lower + all_upper

    count_by_letter_combo = {}
    for a, b in zip(upper_then_lower, lower_then_upper):
        with open(file_name) as f:
            heap = []
            while True:
                c = f.read(1)
                if c == '\n':
                    break

                is_upper = c.isupper()

                opp_polar = c.upper() if c.islower() else c.lower()

                if not heap:
                    heap.append(c)
                elif heap[-1] == opp_polar:
                    heap.pop()
                else:
                    heap.append(c)

        heap_copy = deepcopy(heap)

        heap = []
        for c in heap_copy:

            is_upper = c.isupper()

            opp_polar = c.upper() if c.islower() else c.lower()

            if not heap:
                heap.append(c)
            elif heap[-1] == opp_polar:
                heap.pop()
            else:
                heap.append(c)

        count_by_letter_combo[(a, b)] = len(heap)

    return min(count_by_letter_combo.items(), key=lambda x: x[1])


if __name__ == '__main__':
    file_name = 'day_5_input.txt'
    print(p1(file_name))
    print(p2(file_name))
