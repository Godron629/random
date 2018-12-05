import numpy as np

def parse_claim(claim):
    claim_id, rest = claim.split('@ ')
    claim_id = claim_id[1:]
    top_offset, rest = rest.split(',')
    left_offset, rest = rest.split(':')
    width, rest = rest.split('x')
    height, rest = rest.split('\n')
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
    fabric = np.zeros((1000, 1000))
    with open(file_name) as f:
        for line in f.readlines():
            claim = parse_claim(line)

            top_offset = claim['top_offset']
            left_offset = claim['left_offset']

            height = min(top_offset + claim['height'], 999)
            width = min(top_offset + claim['width'], 999)

            # this indexing is wrong
            fabric[:claim['top_offset'], height] += 1.0
            fabric[claim['left_offset'], width:] +=  1.0

    return np.count_nonzero(fabric > 1)

if __name__ == '__main__':
    print(get_fabric_overlap('day_3_input_part_1.txt'))