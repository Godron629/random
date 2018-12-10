import string
from copy import deepcopy

from util import read_input

def p1(file_name):
    with open(file_name) as f:
        heap = []
        while True:
            c = f.read(1)
            if c == '\n':
                break
            add_to_heap(c, heap)
    print(len(heap))

def add_to_heap(c, heap):
    opp_polar = c.upper() if c.islower() else c.lower()
    if not heap:
        heap.append(c)
    elif heap[-1] == opp_polar:
        heap.pop()
    else:
        heap.append(c)

def p2(file_name):

    count_by_letter = {}
    data = read_input(file_name)

    for a in string.ascii_lowercase:
        heap = []
        for c in data[0]:
            if c.lower() != a:
                heap.append(c)

        new_heap = []
        for c in heap:
            add_to_heap(c, new_heap)
        count_by_letter[a] = len(new_heap)

    return min(count_by_letter.items(), key=lambda x: x[1])


if __name__ == '__main__':
    file_name = 'day_5_input.txt'
    print(p1(file_name))
    print(p2(file_name))
