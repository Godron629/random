from util import read_input

import numpy as np

def parse_claim(claim):
    claim_id, rest = claim.split('@ ')
    claim_id = claim_id[1:]
    left_offset, rest = rest.split(',')
    top_offset, rest = rest.split(':')
    width, height = rest.split('x')

    return {
        'id': claim_id.strip(),
        'top_offset': int(top_offset.strip()),
        'left_offset': int(left_offset.strip()),
        'width': int(width.strip()),
        'height': int(height.strip()),
    }

def get_fabric_overlap(file_name: str) -> int:
    '''
    Return square pixel area of overlapping fabric
    '''
    data = read_input('day_3_input_part_1.txt')
    fabric = np.zeros((1000, 1000))
    for line in data:
        claim = parse_claim(line)

        top_offset = claim['top_offset']
        left_offset = claim['left_offset']

        for i in range(top_offset, top_offset + claim['height']):
            for j in range(left_offset, left_offset + claim['width']):
                fabric[i][j] += 1.0

    return np.count_nonzero(fabric > 1)

def find_no_overlap(file_name: str) -> int:
    '''
    Return to claim id of the only claim that
    doesn't overlap any others.
    '''
    fabric = np.zeros((1000, 1000))
    with open(file_name) as f:
        for line in f.readlines():
            claim = parse_claim(line)

            top_offset = claim['top_offset']
            left_offset = claim['left_offset']
            height = claim['height']
            width = claim['width']

            for i in range(top_offset, top_offset + height):
                for j in range(left_offset, left_offset + width):
                    fabric[i][j] += 1.0

    with open(file_name) as f:
        for line in f.readlines():
            claim = parse_claim(line)

            top_offset = claim['top_offset']
            left_offset = claim['left_offset']
            height = claim['height']
            width = claim['width']

            ok = True
            for i in range(top_offset, top_offset + height):
                for j in range(left_offset, left_offset + width):
                    if fabric[i][j] > 1.0:
                        ok = False
            if ok:
                return claim['id']

if __name__ == '__main__':
    print(get_fabric_overlap('day_3_input_part_1.txt'))
    print(find_no_overlap('day_3_input_part_1.txt'))