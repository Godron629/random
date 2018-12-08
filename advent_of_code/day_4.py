
from util import read_input
from datetime import datetime
from statistics import mode, StatisticsError

DATE_FORMAT = '%Y-%m-%d %H:%M'

def p1(file_name):
    data = read_input(file_name)
    data.sort(key=lambda x: datetime.strptime(x[1: 17], DATE_FORMAT))
    current_guard = None
    current_start = None
    current_end = None
    guards = {}
    for note in data:
        if 'begins' in note:
            current_guard = note
            guard_id = note.split('#')[1]
            guard_id = guard_id.split(' ')[0]
            if guard_id not in guards:
                guards[guard_id] = []
        elif 'asleep' in note:
            current_start = int(note[15:17])
        elif 'wakes' in note:
            current_end = int(note[15:17])
            guards[guard_id].extend(list(range(current_start, current_end)))

    most_sleep = max(guards.items(), key=lambda x: len(x[1]))
    _id = int(most_sleep[0])
    minute = mode(most_sleep[1])

    return _id * minute

def p2(file_name):
    data = read_input(file_name)
    data.sort(key=lambda x: datetime.strptime(x[1: 17], DATE_FORMAT))
    current_guard = None
    current_start = None
    current_end = None
    guards = {}
    for note in data:
        if 'begins' in note:
            current_guard = note
            guard_id = note.split('#')[1]
            guard_id = guard_id.split(' ')[0]
            if guard_id not in guards:
                guards[guard_id] = []
        elif 'asleep' in note:
            current_start = int(note[15:17])
        elif 'wakes' in note:
            current_end = int(note[15:17])
            guards[guard_id].extend(list(range(current_start, current_end)))

    most_frequent = None
    for guard_id, times in guards.items():
        minutes = dict.fromkeys(range(60), 0)
        for minute in times:
            minutes[minute] += 1
        most_minute = max(minutes.items(), key=lambda x: x[1])
        if most_frequent is None:
            most_frequent = (guard_id, most_minute[0], most_minute[1])
        else:
            is_bigger = most_minute[1] > most_frequent[2]
            if is_bigger:
                most_frequent = (guard_id, most_minute[0], most_minute[1])
    return int(most_frequent[0]) * most_frequent[1]


if __name__ == '__main__':
    file_name = 'day_4_input.txt'
    print(p1(file_name))
    print(p2(file_name))