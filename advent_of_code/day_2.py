
def compute_checksum(file_name: str) -> int:
    '''
    Return the product of the number of strings that have exactly 2
    of the same letter and that have exactly 3 of the same letter.
    If a string has multiple 2's or 3's, only one is counted.

    https://adventofcode.com/2018/day/2
    '''
    exactly_2 = 0
    exactly_3 = 0
    with open(file_name) as f:
        for line in f.readlines():
            characters = list(line.strip())
            character_count = {c: 0 for c in characters}
            for character in list(line.strip()):
                character_count[character] += 1
            for count in set(character_count.values()):
                if count == 2:
                    exactly_2 += 1
                if count == 3:
                    exactly_3 += 1
    return exactly_2 * exactly_3

def find_very_close_words(file_name: str) -> str:
    '''
    From a list of words, find the pair that differs in
    the same index by one +- character. Return the common
    parts of that those strings.

    https://adventofcode.com/2018/day/2
    '''
    with open(file_name) as f:
        all_lines = list(f.readlines())
        all_lines = [x.strip() for x in all_lines]

    for i, current in enumerate(all_lines):
        if i == 0:
            continue
        for other in all_lines:
            same = [c1 for c1, c2 in zip(current, other) if c1 == c2]
            if len(same) == len(current) - 1:
                return ''.join(same)


if __name__ == '__main__':
    print(compute_checksum('day_2_input_part_1.txt'))
    print(find_very_close_words('day_2_input_part_1.txt'))