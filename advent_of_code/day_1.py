
def frequency_calculator_part_1(file_name: str) -> int:
    '''
    Return the sum of a list of frequency changes

    https://adventofcode.com/2018/day/1
    '''
    frequency = 0
    with open(file_name) as f:
        for line in f.readlines():
            frequency += eval(line)
    return frequency

def frequency_calculator_part_2(file_name: str) -> int:
    '''
    Repeatedly sum a list of frequency changes until the same
    frequency is found twice, return that frequency.

    https://adventofcode.com/2018/day/1#part2
    '''
    frequency = 0
    seen_frequencies = set()
    with open(file_name) as f:
        all_lines = list(f.readlines())

    seen_double = False
    while not seen_double:
        for line in all_lines:
            frequency += eval(line)
            if frequency in seen_frequencies:
                seen_double = True
                break
            seen_frequencies.add(frequency)
    return frequency

if __name__ == '__main__':
    print(frequency_calculator_part_1('day_1_input_part_1.txt'))
    print(frequency_calculator_part_2('day_1_input_part_2.txt'))